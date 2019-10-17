Program Test1;
var
    n: Integer;
    a, b: Integer;
    r: Real;
    t: array [ 1 .. 5 ] of Boolean;

    function Factorial( n: integer) : integer;
    begin
        if n <= 1 then
            Factorial := 1
        else
            Factorial := n * Factorial( n - 1 );
        n := n * Factorial( n - 1 )
    end;

    procedure Print;
    begin
        WriteLn('Hello world!')
    end;

begin
    t[1] := t[2];
    a := 1 + 2;
    WriteLn( a );
    b := 3 * a div 2;
    WriteLn( b );
    if a = b then
        a := -a
    else
        b := -a;
    WriteLn( a );
    WriteLn( b );
    n := 1;
    while n < 4 do
    begin
        WriteLn( n );
        a := (a + 1) / 3;
        b := b - 1;
        n := n + 1;
    end;
    WriteLn( n );
    WriteLn( n );
end.
