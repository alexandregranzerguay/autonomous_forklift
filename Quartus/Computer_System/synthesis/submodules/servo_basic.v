// Initial attempt at stepper motor control
module servo_basic(input clock_clk, input reset_low, output reg pwm_out, output high, output gnd);
	reg next_out;
	reg [31:0] count;
	
	localparam totalTime = 100000000;
	localparam halfTime = 70000000;
	
	// Move FSM when clock cycles
	always @(clock_clk or reset_low) begin
		if (reset_low == 0) begin
			count <= 0;
		end
		else if (clock_clk == 1) begin
			count <= count + 1;
		end
		if (count == totalTime - 1) begin
			count <= 0;
		end
	end
	
	always @(count) begin
		if (count > halfTime) begin
			pwm_out <= 0;
		end
		else begin
			pwm_out <= 1;
		end
	end
	
	assign high = 1;
	assign gnd = 0;
	
endmodule