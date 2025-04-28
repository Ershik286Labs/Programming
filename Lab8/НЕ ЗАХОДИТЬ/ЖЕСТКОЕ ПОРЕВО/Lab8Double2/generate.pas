unit generate;

{$mode ObjFPC}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, StdCtrls, ComCtrls;

procedure generationMain(FileName: string; ProgressBar: TProgressBar);

implementation

type
  TPersonRecord = packed record
    Name: array[0..49] of Char;    // 50 символов
    Surname: array[0..49] of Char; // 50 символов
    Number: Integer;               // 4 байта (должно быть не 43)
    TempMemory: LongInt;           // Дополнительное поле
  end;

const
  EnglishNames: array[0..19] of string = (
    'Alice', 'Bob', 'Charlie', 'David', 'Eve',
    'Frank', 'Grace', 'Henry', 'Ivy', 'Jack',
    'Kate', 'Liam', 'Mia', 'Noah', 'Olivia',
    'Peter', 'Quinn', 'Rose', 'Sam', 'Tom'
  );
  EnglishSurnames: array[0..19] of string = (
    'Smith', 'Johnson', 'Williams', 'Brown', 'Jones',
    'Garcia', 'Miller', 'Davis', 'Rodriguez', 'Martinez',
    'Hernandez', 'Lopez', 'Gonzalez', 'Wilson', 'Anderson',
    'Thomas', 'Taylor', 'Moore', 'Jackson', 'Martin'
  );
  TargetSize = 1 * 1024 * 1024 * 1024; // 1 ГБ в байтах

procedure generationMain(FileName: string; ProgressBar: TProgressBar);
var
  f: TFileStream;
  MyRec: TPersonRecord;
  TotalWritten: int64;
  nameIndex, surnameIndex, procent: integer;
  BytesWritten: Integer;
  oneProcent, lastProcent: int64;
begin
  oneProcent := TargetSize div 100;
  lastProcent := -1;

  ProgressBar.Min := 0;
  ProgressBar.Max := 100;
  ProgressBar.Position := 0;

  Randomize;
  f := TFileStream.Create(FileName, fmCreate);
  try
    TotalWritten := 0;
    while TotalWritten < TargetSize do
    begin
      nameIndex := Random(20);
      surnameIndex := Random(20);
      MyRec.Name := EnglishNames[nameIndex];
      MyRec.SurName := EnglishSurnames[surnameIndex];
      MyRec.Number := Random(10000);
      //ShowMessage(IntToStr(MyRec.Value));
      f.WriteBuffer(MyRec, SizeOf(MyRec));

      BytesWritten := SizeOf(MyRec);
      Inc(TotalWritten, BytesWritten);

      // Обновляем прогресс бар
      procent := TotalWritten div oneProcent;
      if (procent > lastProcent) then
      begin
        ProgressBar.Position := procent;
        lastProcent := procent;
        Application.ProcessMessages; // Обновляем GUI
      end;
    end;

    // Вместо ProgressBar.Lines.Add используем ShowMessage или другой способ вывода
    ShowMessage('Генерация файла завершена!');
    ProgressBar.Position := 0;
  finally
    f.Free;
  end;
end;

end.
