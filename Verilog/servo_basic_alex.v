// Initial attempt at stepper motor control
module servo_basic(input clock_clk, input reset_low, output reg pwm_out, output high, output gnd);
	reg next_out;
	reg [31:0] count;
	
	localparam totalTime = 100000000;
	localparam halfTime = 70000000;
	
	always @(count) begin
		if (count > halfTime) begin
			pwm_out <= 0;
		end
		else begin
			pwm_out <= 1;
		end
	end
	
<<<<<<< HEAD:Verilog/servo_basic_alex.v
	// Move FSM when clock cycles
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
=======
	assign high = 1;
	assign gnd = 0;
	
>>>>>>> e809a803e611a80a96479a262e2fc2f971a10a1c:Verilog/servo_basic.v
endmodule