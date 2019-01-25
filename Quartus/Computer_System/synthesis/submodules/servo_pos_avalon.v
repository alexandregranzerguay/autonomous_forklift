// Servo drive control module
module servo_pos_avalon(input clock_clk, input reset_low, input write, input cs, input [31:0] writedata, output pwm_out);
	reg [31:0] speed;
	
	always @(posedge clock_clk or negedge reset_low) begin
		if (reset_low == 0) begin
			speed <= 0;
		end
		else if (cs == 1 && write == 1) begin
			speed <= writedata;
		end
	end
	
	servo_pos_drive servo(clock_clk, reset_low, speed, pwm_out);
	
endmodule