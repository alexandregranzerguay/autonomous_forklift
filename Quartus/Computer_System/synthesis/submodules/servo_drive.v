// Servo drive control module
module servo_drive(input clock_clk, input reset_low, input [31:0] pulseTime, output reg pwm_out);
	reg [31:0] count;
	
	// Total pulse width
	localparam totalTime = 2000000;
	//localparam totalTime = 10;
	
	// Handle resets and increase count on positive clock edges
	always @(posedge clock_clk or negedge reset_low) begin
		if (reset_low == 0) begin
			count <= 0;
		end
		else begin
			count <= count + 1;
			if (count == totalTime - 1) begin
				count <= 0;
			end
		end
	end
	
	// Determine pulse output based on count and pulseTime
	always @(count) begin
		if (count >= pulseTime) begin
			pwm_out <= 0;
		end
		else begin
			pwm_out <= 1;
		end
	end
	
endmodule