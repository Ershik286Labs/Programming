﻿Unit Fractal;
{-------------------------------}
Interface

Uses GraphABC;
type
  Point = record
    x, y: Double;
end;
   Procedure hilbertCurve(var points: array of Point; x, y, xi, xj, yi, yj: Double; n: Integer);
   Procedure drawHilbertCurve(const points: array of Point);
{-------------------------------}
implementation
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
var i:integer;
begin
  if Length(points) = 0 then Exit;

  MoveTo(Round(points[0].x), Round(points[0].y));
  for i := 1 to High(points) do
  begin
    LineTo(Round(points[i].x), Round(points[i].y));
  end;
end;

initialization
end .