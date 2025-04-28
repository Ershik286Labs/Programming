unit checking;

{$mode ObjFPC}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, StdCtrls, ComCtrls;

type
  TPersonRecord = packed record
    Name: array[0..49] of Char;    // 50 символов
    Surname: array[0..49] of Char; // 50 символов
    Number: Integer;
    TempMemory: LongInt;
  end;

const
  TargetSize = 1 * 1024 * 1024 * 1024; // 1 ГБ в байтах

procedure mainCheck(keySort: integer; ProgressBar: TProgressBar);

implementation

function CompareByName(const A, B: TPersonRecord): Integer;
begin
  Result := CompareStr(A.Name, B.Name);
  if Result = 0 then
    Result := CompareStr(A.Surname, B.Surname);
end;

function CompareByNumber(const A, B: TPersonRecord): Integer;
begin
  Result := A.Number - B.Number;
end;

procedure mainCheck(keySort: integer; ProgressBar: TProgressBar);
var
  F: TFileStream;
  MyRec, PrevRec: TPersonRecord;
  TotalRead: Int64;
  oneProcent, lastProcent: Int64;
  procent: Integer;
  IsSorted: Boolean;
  fileName:string;
  CompareFunc: function(const A, B: TPersonRecord): Integer;
begin
  // Выбираем функцию сравнения и файл в зависимости от ключа сортировки
  //ShowMessage(IntToStr(keySort));
  if keySort = 2 then
  begin
      CompareFunc := @CompareByNumber;
      fileName := 'output_sorted_by_number.dat';
  end
  else
  begin
      CompareFunc := @CompareByName;
      fileName := 'output_sorted_by_name.dat';
  end;

  if not FileExists(fileName) then
  begin
    ShowMessage('Файл не существует!');
    Exit;
  end;
  lastProcent := -1;

  F := TFileStream.Create(fileName, fmOpenRead);
  try
    TotalRead := 0;
    oneProcent := F.Size div 100;

    // Читаем первую запись
    if F.Read(PrevRec, SizeOf(TPersonRecord)) <> SizeOf(TPersonRecord) then
    begin
      ShowMessage('Файл пуст!');
      Exit;
    end;
    Inc(TotalRead, SizeOf(TPersonRecord));

    IsSorted := True;

    while TotalRead < F.Size do
    begin
      // Читаем следующую запись
      if F.Read(MyRec, SizeOf(TPersonRecord)) <> SizeOf(TPersonRecord) then
        Break;

      Inc(TotalRead, SizeOf(TPersonRecord));

      // Проверяем сортировку
      if CompareFunc(PrevRec, MyRec) > 0 then
      begin
        IsSorted := False;
        // Не прерываем проверку, чтобы показать полный прогресс
      end;

      PrevRec := MyRec;

      // Обновляем прогресс-бар
      if oneProcent > 0 then
      begin
        procent := TotalRead div oneProcent;
        if (procent > lastProcent) then
        begin
          ProgressBar.Position := procent;
          lastProcent := procent;
          Application.ProcessMessages;
        end;
      end;
    end;

    // Финализация прогресс-бара
    ProgressBar.Position := 100;
    Application.ProcessMessages;

    // Показываем результат проверки
    if IsSorted then
      ShowMessage('Файл корректно отсортирован!')
    else
      ShowMessage('Файл НЕ отсортирован! Обнаружены нарушения порядка.');

  finally
    F.Free;
  end;
end;

end.
