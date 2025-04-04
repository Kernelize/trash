`timescale 1ns/1ps

module parking(
  input clk,             // 时钟信号
  input reset_n,           // 复位信号（低有效）
  input sensor_entrance,   // 入口传感器信号
  input sensor_exit,       // 出口传感器信号
  input [1:0] password_1,  // 密码1
  input [1:0] password_2,  // 密码2
  output [6:0] HEX_1,      // 数码管1输出
  output [6:0] HEX_2,       // 数码管2输出
  output [2:0] state
);

  // 中间信号，用于连接 `fsm_controller` 和 `seven_segment_decoder`
  wire [7:0] hex_1_ascii;
  wire [7:0] hex_2_ascii;

  // 实例化 `fsm_controller` 模块
  fsm_controller fsm_inst (
    .clock(clk),
    .reset_n(reset_n),
    .sensor_entrance(sensor_entrance),
    .sensor_exit(sensor_exit),
    .password_1(password_1),
    .password_2(password_2),
    .hex_1(hex_1_ascii),
    .hex_2(hex_2_ascii),
    .state(state)
  );

  // 实例化两个 `seven_segment_decoder` 模块
  seven_segment_decoder decoder_1 (
    .ascii(hex_1_ascii),
    .segments(HEX_1)
  );

  seven_segment_decoder decoder_2 (
    .ascii(hex_2_ascii),
    .segments(HEX_2)
  );

endmodule

module fsm_controller(
  input clock,// clock of the circuit 
  input reset_n,// reset  
  input sensor_entrance,
  input sensor_exit,
  input[1:0] password_1,
  input[1:0] password_2,
  output[2:0] state,
  output reg[7:0] hex_1,
  output reg[7:0] hex_2
);

// FSM States 
  localparam IDLE=3'b000;
  localparam WAIT_PASSWORD=3'b001;
  localparam RIGHT_PASS=3'b010;
  localparam WRONG_PASSWORD=3'b011;
  localparam ENTER=3'b100;
  localparam STOP=3'b101;

  assign state = current_state;

  reg[2:0] current_state, next_state;

  reg[7:0] vacant_space;

  // vacant_space counter
  always @(posedge clock or negedge reset_n) begin
    if (!reset_n)
      vacant_space <= 3;
    else if (current_state == RIGHT_PASS && sensor_exit)
      if (vacant_space > 0)
        vacant_space <= vacant_space - 1;
  end

  // current state registers 
  always @(posedge clock or negedge reset_n) 
    begin 
      if(!reset_n)
        current_state <= IDLE;
      else 
        current_state <= next_state;
    end 

  // next state 
  always @(*)
  begin
    case(current_state)
      IDLE: begin 
        if (sensor_entrance == 1) 
          next_state <= WAIT_PASSWORD;
        else 
          next_state <= IDLE;
      end 

      WAIT_PASSWORD:begin 
        if (password_1 == 2'b00 && password_2 == 2'b11) // password_1 == 0 && password_2 == 3
          next_state <= RIGHT_PASS;
        else
          next_state <= WRONG_PASSWORD;
      end 

      RIGHT_PASS:begin 
        if (sensor_exit == 1) 
          next_state <= ENTER;
        else 
          next_state <= RIGHT_PASS;
      end 

      WRONG_PASSWORD:begin // game done
        if (password_1 == 2'b00 && password_2 == 2'b11)
          next_state <= RIGHT_PASS;
        else
          next_state <= WRONG_PASSWORD;
      end 

      ENTER:begin 
        if (sensor_entrance == 1) 
          next_state <= STOP;
        else 
          next_state <= IDLE;
      end

      STOP:begin 
        next_state <= WAIT_PASSWORD;
      end

      default: next_state <= IDLE;
    endcase
  end
  
  // outputs
  always @(*)
  begin
    hex_1 = 8'd0 + 8'd48;
    hex_2 = 8'd0 + 8'd48;

    case (current_state)
      IDLE: begin
        // current vacant space
        hex_1 <= vacant_space / 10 + 8'd48;
        hex_2 <= vacant_space % 10 + 8'd48;
      end

      WAIT_PASSWORD: begin
        // 'E' 'N'
        hex_1 <= 8'd69;
        hex_2 <= 8'd78;
      end

      RIGHT_PASS: begin
        // 'G' 'O'
        hex_1 <= 8'd71;
        hex_2 <= 8'd79;
      end

      WRONG_PASSWORD: begin
        // 'E' 'E'
        hex_1 <= 8'd69;
        hex_2 <= 8'd69;
      end

      STOP: begin
        // 'S' 'P'
        hex_1 <= 8'd83;
        hex_2 <= 8'd80;
      end

      default: begin
        hex_1 <= hex_1;
        hex_2 <= hex_2;
      end
    endcase
  end

endmodule


module seven_segment_decoder (
  input [7:0] ascii,        // 输入ASCII码
  output reg [6:0] segments // 输出数字管段信号（a-g）
);
  always @(*) begin
    case (ascii)
      // 数字 0-9
      8'h30: segments = 7'b0111111; // 0
      8'h31: segments = 7'b0000110; // 1
      8'h32: segments = 7'b1011011; // 2
      8'h33: segments = 7'b1001111; // 3
      8'h34: segments = 7'b1100110; // 4
      8'h35: segments = 7'b1101101; // 5
      8'h36: segments = 7'b1111101; // 6
      8'h37: segments = 7'b0000111; // 7
      8'h38: segments = 7'b1111111; // 8
      8'h39: segments = 7'b1101111; // 9

      // 字母 A-Z
      8'h41: segments = 7'b1110111; // A
      8'h42: segments = 7'b1111100; // B
      8'h43: segments = 7'b0111001; // C
      8'h44: segments = 7'b1011110; // D
      8'h45: segments = 7'b1111001; // E
      8'h46: segments = 7'b1110001; // F
      8'h47: segments = 7'b0111101; // G
      8'h48: segments = 7'b1110110; // H
      8'h49: segments = 7'b0000110; // I
      8'h4A: segments = 7'b0011110; // J
      8'h4B: segments = 7'b1110111; // K (approximation)
      8'h4C: segments = 7'b0111000; // L
      8'h4D: segments = 7'b1010100; // M (approximation)
      8'h4E: segments = 7'b1010101; // N (approximation)
      8'h4F: segments = 7'b0111111; // O
      8'h50: segments = 7'b1110011; // P
      8'h51: segments = 7'b1100111; // Q (approximation)
      8'h52: segments = 7'b1010000; // R
      8'h53: segments = 7'b1101101; // S
      8'h54: segments = 7'b1111000; // T
      8'h55: segments = 7'b0111110; // U
      8'h56: segments = 7'b0011100; // V
      8'h57: segments = 7'b1011100; // W (approximation)
      8'h58: segments = 7'b1110110; // X (approximation)
      8'h59: segments = 7'b1101110; // Y
      8'h5A: segments = 7'b1011011; // Z

      // 小写字母 a-z
      8'h61: segments = 7'b1011111; // a
      8'h62: segments = 7'b1111100; // b
      8'h63: segments = 7'b1011000; // c
      8'h64: segments = 7'b1011110; // d
      8'h65: segments = 7'b1111011; // e
      8'h66: segments = 7'b1110001; // f
      8'h67: segments = 7'b1101111; // g
      8'h68: segments = 7'b1110100; // h
      8'h69: segments = 7'b0000100; // i
      8'h6A: segments = 7'b0001110; // j
      8'h6B: segments = 7'b1110111; // k (approximation)
      8'h6C: segments = 7'b0111000; // l
      8'h6D: segments = 7'b1010100; // m (approximation)
      8'h6E: segments = 7'b1010100; // n
      8'h6F: segments = 7'b1011111; // o
      8'h70: segments = 7'b1110011; // p
      8'h71: segments = 7'b1100111; // q
      8'h72: segments = 7'b1010000; // r
      8'h73: segments = 7'b1101101; // s
      8'h74: segments = 7'b1111000; // t
      8'h75: segments = 7'b0011110; // u
      8'h76: segments = 7'b0011100; // v
      8'h77: segments = 7'b1011100; // w (approximation)
      8'h78: segments = 7'b1110110; // x (approximation)
      8'h79: segments = 7'b1101110; // y
      8'h7A: segments = 7'b1011011; // z

      // 标点符号
      8'h2D: segments = 7'b0000001; // -
      8'h2E: segments = 7'b0000000; // .
      8'h20: segments = 7'b0000000; // 空格

      default: segments = 7'b0000000; // 默认空显示
    endcase
  end
endmodule
