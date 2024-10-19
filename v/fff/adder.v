module adder #(parameter WIDTH = 8) (
  input wire [WIDTH-1:0] a, b,
  output wire [WIDTH-1:0] sum
);
  assign sum = a + b;
endmodule

module adder_tb();
  adder #(.WIDTH(8)) U_adder (
    .a(8'b00000001),
    .b(8'b00000010),
    .sum(sum)
  );
endmodule
