unit Sort;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, StdCtrls, ComCtrls;

const
  MAX_MEMORY = 100 * 1024 * 1024; // 100 МБ

type
  TPersonRecord = packed record
    Name: array[0..49] of Char;    // 50 символов
    Surname: array[0..49] of Char; // 50 символов
    Number: Integer;
    TempMemory: LongInt;
  end;

  TCompareFunction = function(const A, B: TPersonRecord): Integer;

procedure SortBinaryFile(const InputFile, OutputFile: string; CompareFunc: TCompareFunction; ProgressBar: TProgressBar);
procedure sortMain(keySort: integer; fileName: string; ProgressBar: TProgressBar);
procedure updateProgressBar(ProgressBar: TProgressBar);

var
  currentProgress:integer;

implementation

procedure SortBinaryFile(const InputFile, OutputFile: string; CompareFunc: TCompareFunction; ProgressBar: TProgressBar);
var
  TempFiles: array of string;
  InputFS, OutputFS: TFileStream;
  Buffer: array of TPersonRecord;
  ChunkSize, ChunksCount: Integer;
  I, J: Integer;

  // Быстрая сортировка
  procedure QuickSort(var A: array of TPersonRecord; L, R: Integer);
  var
    I, J: Integer;
    Pivot, Temp: TPersonRecord;
  begin
    I := L;
    J := R;
    Pivot := A[(L + R) div 2];

    repeat
      while CompareFunc(A[I], Pivot) < 0 do Inc(I);
      while CompareFunc(A[J], Pivot) > 0 do Dec(J);

      if I <= J then
      begin
        Temp := A[I];
        A[I] := A[J];
        A[J] := Temp;
        Inc(I);
        Dec(J);
      end;
    until I > J;

    if L < J then QuickSort(A, L, J);
    if I < R then QuickSort(A, I, R);
  end;

  // Слияние отсортированных файлов
  procedure MergeFiles(const FileList: array of string; const OutputFile: string);
  var
    FileStreams: array of TFileStream;
    CurrentRecords: array of TPersonRecord;
    MinIndex: Integer;
    OutputFS: TFileStream;
    HasData: Boolean;
    i: Integer;
  begin
    SetLength(FileStreams, Length(FileList));
    SetLength(CurrentRecords, Length(FileList));

    // Открываем все временные файлы
    for i := 0 to High(FileList) do
    begin
      FileStreams[i] := TFileStream.Create(FileList[i], fmOpenRead);
      if FileStreams[i].Read(CurrentRecords[i], SizeOf(TPersonRecord)) <> SizeOf(TPersonRecord) then
        CurrentRecords[i].Number := MaxInt; // Помечаем как "пустой"
    end;

    OutputFS := TFileStream.Create(OutputFile, fmCreate);
    try
      repeat
        // Находим минимальный элемент
        MinIndex := -1;
        HasData := False;

        for i := 0 to High(CurrentRecords) do
        begin
          if CurrentRecords[i].Number <> MaxInt then
          begin
            HasData := True;
            if (MinIndex = -1) or (CompareFunc(CurrentRecords[i], CurrentRecords[MinIndex]) < 0) then
              MinIndex := i;
          end;
        end;

        if not HasData then Break;

        // Записываем минимальный элемент в выходной файл
        OutputFS.WriteBuffer(CurrentRecords[MinIndex], SizeOf(TPersonRecord));

        // Читаем следующий элемент из файла, откуда взяли текущий минимальный
        if FileStreams[MinIndex].Read(CurrentRecords[MinIndex], SizeOf(TPersonRecord)) <> SizeOf(TPersonRecord) then
          CurrentRecords[MinIndex].Number := MaxInt; // Помечаем как "пустой"
      until False;
    finally
      OutputFS.Free;
      for i := 0 to High(FileStreams) do
        FileStreams[i].Free;
    end;
  end;

begin
  // Определяем размер чанка, который поместится в памяти
  ChunkSize := MAX_MEMORY div SizeOf(TPersonRecord);
  SetLength(Buffer, ChunkSize);

  // 1. Разделение на отсортированные чанки
  InputFS := TFileStream.Create(InputFile, fmOpenRead);
  try
    ChunksCount := 0;
    while InputFS.Position < InputFS.Size do
    begin
      // Читаем чанк данных
      I := 0;
      while (I < ChunkSize) and (InputFS.Position < InputFS.Size) do
      begin
        InputFS.ReadBuffer(Buffer[I], SizeOf(TPersonRecord));
        Inc(I);
      end;

      // Сортируем чанк в памяти
      QuickSort(Buffer, 0, I - 1);

      // Сохраняем временный файл
      SetLength(TempFiles, Length(TempFiles) + 1);
      TempFiles[High(TempFiles)] := ChangeFileExt(InputFile, '.tmp' + IntToStr(ChunksCount));

      OutputFS := TFileStream.Create(TempFiles[High(TempFiles)], fmCreate);
      try
        for J := 0 to I - 1 do
          OutputFS.WriteBuffer(Buffer[J], SizeOf(TPersonRecord));
      finally
        OutputFS.Free;
      end;

      Inc(ChunksCount);
      currentProgress := currentProgress + 8;
      updateProgressBar(ProgressBar);
    end;
  finally
    InputFS.Free;
  end;

  // 2. Многофазное слияние
  if Length(TempFiles) > 0 then
  begin
    if Length(TempFiles) = 1 then
    begin
      // Если только один чанк, просто переименовываем его
      RenameFile(TempFiles[0], OutputFile);
    end
    else
    begin
      // Сливаем все временные файлы в выходной
      MergeFiles(TempFiles, OutputFile);
    end;
  end;

  // Удаляем временные файлы
  for I := 0 to High(TempFiles) do
    if FileExists(TempFiles[I]) then
      DeleteFile(TempFiles[I]);
  currentProgress := 100;
  updateProgressBar(ProgressBar);
end;

// Функция сравнения для сортировки по фамилии и имени
function CompareBySurnameAndName(const A, B: TPersonRecord): Integer;
var
  SurnameCompare, NameCompare: Integer;
begin
  SurnameCompare := CompareStr(A.Surname, B.Surname);
  if SurnameCompare <> 0 then
    Result := SurnameCompare
  else
  begin
    NameCompare := CompareStr(A.Name, B.Name);
    if NameCompare <> 0 then
      Result := NameCompare
    else
      Result := A.Number - B.Number;
  end;
end;

// Функция сравнения для сортировки по номеру
function CompareByNumber(const A, B: TPersonRecord): Integer;
begin
  Result := A.Number - B.Number;
end;

procedure sortMain(keySort: integer; fileName: string; ProgressBar: TProgressBar);
begin
  currentProgress := 0;
  if keySort = 1  then
     SortBinaryFile(fileName, 'output_sorted_by_name.dat', @CompareBySurnameAndName, ProgressBar);
  if keySort = 2 then
     SortBinaryFile(fileName, 'output_sorted_by_number.dat', @CompareByNumber, ProgressBar);
end;

procedure updateProgressBar(ProgressBar: TProgressBar);
begin
  ProgressBar.Position := currentProgress;
end;

end.
