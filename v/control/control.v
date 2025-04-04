module control(
    input clk_1Hz, sys_rst_n,
    output [2:0] A_Light, B_Light
);

localparam s0 = 3'b000, s1 = 3'b001, s2 = 3'b010, s3 = 3'b011, s4 = 3'b100;
reg [2:0] state, next_state;

reg [5:0] s;

always @(posedge clk_1Hz)
    s = s + 1;

always @(posedge clk_1Hz, negedge sys_rst_n)
    state <= (sys_rst_n == 1'b0) ? s0 : next_state;

always @(*)
begin
    case  (state)
        s0: next_state = s1;
        s1: begin
            if (s == 6'd40)
                next_state = s2;
            else
                next_state = s1;
        end
    endcase

end

endmodule
