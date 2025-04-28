unit Main;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, StdCtrls, ComCtrls,
  Menus, ActnList, generate, Types, Sort, checking;

type

  { TForm1 }

  TForm1 = class(TForm)
    OpenDialog1: TOpenDialog;
    SelectFile: TButton;
    CheckSort: TButton;
    ToogleSort: TComboBox;
    GenerateBtn: TButton;
    ListBox1: TListBox;
    SortBtn: TButton;
    Sort: TButton;
    ProgressBar: TProgressBar;

    procedure CheckSortClick(Sender: TObject);
    procedure SelectFileClick(Sender: TObject);
    procedure ToogleSortChange(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure GenerateBtnClick(Sender: TObject);
    procedure ListBox1Click(Sender: TObject);
    procedure SortBtnClick(Sender: TObject);
    procedure LoadFileToListBox(const Filename: string; MaxLines: Integer = 100);
  private
      const Filename = 'struct_file.dat';
  public

  end;

var
  Form1: TForm1;
  KeySort : integer;
  flagGenerationFile: boolean;
implementation

{$R *.lfm}

{ TForm1 }

//Создание окна
procedure TForm1.FormCreate(Sender: TObject);
begin
  flagGenerationFile := False;
  KeySort := 0;
end;

//Проверка сортировки
procedure TForm1.CheckSortClick(Sender: TObject);
begin
    mainCheck(keySort, ProgressBar);
end;

//Диалоговое окно для выбора файла
procedure TForm1.SelectFileClick(Sender: TObject);
var
   FilenameLoad:string;
begin
  if OpenDialog1 = nil then
  begin
    OpenDialog1 := TOpenDialog.Create(Self);
    OpenDialog1.Filter := 'Data files (*.dat)|*.dat|All files (*.*)|*.*';
    OpenDialog1.DefaultExt := 'dat';
    OpenDialog1.Title := 'Выберите файл для загрузки';
  end;

  if OpenDialog1.Execute then
  begin
    // Загружаем выбранный файл
    FilenameLoad := OpenDialog1.FileName;
    flagGenerationFile := true;
    LoadFileToListBox(FilenameLoad, 100); // Ваша процедура для загрузки файла в ListBox

    // Обновляем статус
    ShowMessage('Загружен файл: ' + ExtractFileName(FilenameLoad));
  end;
end;

//Выбор ключа сортировки
procedure TForm1.ToogleSortChange(Sender: TObject);
begin
  KeySort := ToogleSort.ItemIndex + 1;
  ShowMessage('Выбран ключ сортировки: ' + IntToStr(KeySort));
end;

//Кнопка генерации файла
procedure TForm1.GenerateBtnClick(Sender: TObject);
begin
   generationMain(Filename, ProgressBar);
   flagGenerationFile := true;
end;

//область для листания файла
procedure TForm1.ListBox1Click(Sender: TObject);
var
   FilenameLoad: string;
begin

end;

//событие нажатие клавиши
procedure TForm1.SortBtnClick(Sender: TObject);
begin
  ShowMessage('Сортировка началась, пожалуйста, подождите. Среднее время ожидания - 1.5 - 2 минуты.');
    if not FileExists(Filename) then
      begin
        ShowMessage('Файл не найден!');
        Exit;
      end;
   if (flagGenerationFile = false) then begin
      ShowMessage('Сначала сгенерируйте файл!');
      Exit;
   end;
   if (keySort = 0) then
   begin
      ShowMessage('Сначала выберите ключ сортировки!');
      Exit;
   end;
   sortMain(keySort, Filename, ProgressBar);
   ShowMessage('Сортировка была проведена успешно!');
   ProgressBar.Position := 0;
end;

procedure TForm1.LoadFileToListBox(const Filename: string; MaxLines: Integer = 100);
var
  FS: TFileStream;
  RecordData: TPersonRecord; // Используем вашу структуру записи
  Line: string;
  LinesLoaded: Integer;
begin
  ListBox1.Clear;
  LinesLoaded := 0;

  if not FileExists(Filename) then
  begin
    ShowMessage('Файл не найден!');
    Exit;
  end;

  FS := TFileStream.Create(Filename, fmOpenRead);
  try
    while (FS.Position < FS.Size) and (LinesLoaded < MaxLines) do
    begin
      FS.ReadBuffer(RecordData, SizeOf(TPersonRecord));

      // Форматируем запись для отображения
      Line := Format('%s %s (%d)',
        [Trim(RecordData.Name),
         Trim(RecordData.Surname),
         RecordData.Number]);

      ListBox1.Items.Add(Line);
      Inc(LinesLoaded);
    end;

    if FS.Position < FS.Size then
      ListBox1.Items.Add('... и ещё ' + IntToStr((FS.Size - FS.Position) div SizeOf(TPersonRecord)) + ' записей');

  finally
    FS.Free;
  end;
end;

end.

