// Initial attempt at stepper motor control
module servo_pos_basic(input clock_clk, input reset_low, output reg pwm_out);
	reg [31:0] count;
	
	localparam offTime = 2000000;
	localparam pulseTime = 150000;
	
	// Move FSM when clock cycles
	always @(posedge clock_clk or negedge reset_low) begin
		if (reset_low == 0) begin
			count <= 0;
		end
		else begin
			count <= count + 1;
			if (count == offTime + pulseTime - 1) begin
				count <= 0;
			end
		end
	end
	
	always @(count) begin
		if (count >= pulseTime) begin
			pwm_out <= 0;
		end
		else begin
			pwm_out <= 1;
		end
	end
	
endmodule