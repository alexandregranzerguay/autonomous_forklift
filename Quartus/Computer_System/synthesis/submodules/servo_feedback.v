// Servo drive control module
module servo_feedback(input clock_clk, input reset_low, input pwm_response, output reg [31:0] angle);
	reg [31:0] count;
	
	// Total pulse width
	//localparam totalTime = 10;
	
	// Handle resets and increase count on positive clock edges
	always @(posedge clock_clk or negedge reset_low) begin
		if (reset_low == 0) begin
			count <= 0;
		end
		else begin
			if (pwm_response == 1) begin
				count <= count + 1;
			end
			else begin
				if (count > 0) begin
					angle <= count;
				end
				count <= 0;
			end
		end
	end
	
//	always @(negedge pwm_response) begin
//		if (count > 0) begin
//			angle <= count;
//		end
//		count <= 0;
//	end
	
endmodule