`include "first_counter.v"
module first_counter_tb();

reg clock, reset, enable;
wire [3:0] counter_out;

reg [31:0] a;

initial begin
  $dumpfile("first_counter.vcd");
  $dumpvars(0, first_counter_tb);
  a = 14'h1234;
  $display("a = %h", a);
  $display("time\t Clock Reset Enable Counter");
  $monitor("%g\t %b %b %b %b %b", $time, clock, reset, enable, counter_out, a);
  clock = 1;
  reset = 1;
  enable = 0;
  #5 reset = 1;
  #10 reset = 0;
  #10 enable = 1;
  #100 enable = 0;
  #5 $finish;
end

always begin
  #5 clock = ~clock;
  a = $random;
end

first_counter U_counter (
  .clock(clock),
  .reset(reset),
  .enable(enable),
  .counter_out(counter_out)
);

endmodule
