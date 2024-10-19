// Copyright (c) 2024, Hank. All rights reserved.
module first_counter (
  input wire clock, reset, enable,
  output reg [3:0] counter_out
);

always @ (posedge clock)
begin
  if (reset == 1'b1) begin
    counter_out <= #1 4'b0000;
  end
  else if (enable == 1'b1) begin
    counter_out <= #1 counter_out +1;
  end
end

endmodule
