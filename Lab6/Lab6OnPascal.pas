Uses Crt, GraphABC;

Const
  u = 10;
  p = 5;

Var
  i: Integer;
  size: integer; // Глубина рекурсии

type
  Point = record
    x, y: Double;
  end;

procedure hilbertCurve(var points: array of Point; x, y, xi, xj, yi, yj: Double; n: Integer);
var
  x1, y1: Double;
begin
  if n <= 0 then
  begin
    x1 := x + (xi + yi) / 2;
    y1 := y + (xj + yj) / 2;
    SetLength(points, Length(points) + 1);
    points[High(points)].x := x1;
    points[High(points)].y := y1;
  end
  else
  begin
    hilbertCurve(points, x, y, yi / 2, yj / 2, xi / 2, xj / 2, n - 1);
    hilbertCurve(points, x + xi / 2, y + xj / 2, xi / 2, xj / 2, yi / 2, yj / 2, n - 1);
    hilbertCurve(points, x + xi / 2 + yi / 2, y + xj / 2 + yj / 2, xi / 2, xj / 2, yi / 2, yj / 2, n - 1);
    hilbertCurve(points, x + xi / 2 + yi, y + xj / 2 + yj, -yi / 2, -yj / 2, -xi / 2, -xj / 2, n - 1);
  end;
end;

procedure drawHilbertCurve(const points: array of Point);
var
  i: Integer;
begin
  if Length(points) = 0 then Exit;

  MoveTo(Round(points[0].x), Round(points[0].y));
  for i := 1 to High(points) do
  begin
    LineTo(Round(points[i].x), Round(points[i].y));
  end;
end;

var
  points: array of Point;

Begin
  SetWindowCaption('Фракталы: Кривая Гильберта');
  SetWindowSize(800, 800);
  ClearWindow;
  Writeln('Введите глубину рекурсии');
  readln(size);
  if size > 7 then size := 7;
  SetLength(points, 0);
  hilbertCurve(points, 80, 480, 400, 0, 0, -400, size);

  drawHilbertCurve(points);
  Readln;
End.
