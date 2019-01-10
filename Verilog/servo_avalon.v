// Servo drive control module
module servo_avalon(input clock_clk, input reset_low, input read, input write, input cs, output reg [31:0] readdata, input [31:0] writedata, input pwm_response, output pwm_out);
	//reg next_out;
	//reg [31:0] count;
	reg [31:0] speed;
	wire [31:0] angle;
	
	// Total pulse width
	localparam totalTime = 10;
	
	always @(clock_clk or reset_low) begin
		if (reset_low == 0) begin
			readdata <= 0;
		end
		else if (cs == 1) begin
			if (read == 1) begin
				readdata <= angle;
			end
			else if (write == 1) begin
				speed <= writedata;
			end
		end
	end
	
	servo_drive servo(clock_clk, reset_low, speed, pwm_out);
	servo_feedback feedback(clock_clk, reset_low, pwm_response, angle);
	
endmodule