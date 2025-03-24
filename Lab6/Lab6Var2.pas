uses GraphABC, Fractal;

var
  points: array of Point;
  size: integer;
  whileKey: integer;
  width, stepWidth: integer;
  CenterY, CenterX: integer;
  key:boolean;
  
  
procedure DrawInstructions();  // Новая процедура для отрисовки текста
var i, j:integer;
begin
  // Рисуем текст с инструкциями
  SetBrushColor(clWhite); // Цвет фона
  SetFontColor(clBlack);   // Цвет текста
  
  for i := 0 to 600 do
  begin
    for j := 1 to 5 do
      SetPixel(i, j * 20 + 5 + 1, clBlack);
  end;
  TextOut(10, 10, 'Масштаб: ' + IntToStr(width));  // Выводим текст, указывая координаты и текст
  TextOut(10, 30, 'Для увеличения масштаба нажмите E, для уменьшения нажмите Q');
  TextOut(10, 50, 'Для передвижения фрактала нажимайте клавиши стрелочки');
  TextOut(10, 70, 'Глубина рекурсии: ' + IntToStr(size));
  TextOut(10, 90, 'Для изменения глубины рекурсии нажимайте на клавиши с цифрами');
end;

procedure DrawFractal();
begin
  if (width > 0) and (size >= 0) then
  begin
    SetLength(points, 0);
    hilbertCurve(points, CenterX, CenterY, width, 0, 0, -1 * width, size);
    drawHilbertCurve(points);
  end;
end;

procedure Draw(); // старая процедура Draw
begin
    ClearWindow; // Очищаем окно каждый раз
    DrawFractal();
    DrawInstructions();
end;
 
procedure keyListener(k : integer); begin
    if k = VK_LEFT then CenterX := Round(CenterX - stepWidth / 2); 
    if k = VK_RIGHT then CenterX := Round(CenterX + stepWidth / 2); 
    if k = VK_UP then CenterY := Round(CenterY - stepWidth / 2); 
    if k = VK_DOWN then CenterY := Round(CenterY + stepWidth / 2);

    if k = VK_Q then width := width - stepWidth; // q
    if k = VK_E then width := width + stepWidth;// e
    if (ord('1') <= k) and (k <= ord('9')) then size := k - ord('0');
    Draw();
end;
  
begin
  width := 400;
  stepWidth := 25;
  CenterY := 525;
  CenterX := 50;
  size := 0;
  whileKey := 0;
  
  SetWindowCaption('Фракталы: Кривая Гильберта');
  SetWindowSize(600, 600);
  Draw();
  
  while whileKey = 0 do
  begin
    OnKeyDown := keyListener; 
    if CenterY < 0 then CenterY := 0;
    if CenterX < 0 then CenterX := 0;
  end;
end.