// Initial attempt at stepper motor control
module servo_basic(input clock_clk, input reset_low, output reg pwm_out, output high, output gnd);
	reg [31:0] count;
	
	//localparam totalTime = 2000000;
	//localparam halfTime = 165000;
	localparam totalTime = 4000000;
	localparam halfTime = 330000;
	
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
	
	always @(count) begin
		if (count >= halfTime) begin
			pwm_out <= 0;
		end
		else begin
			pwm_out <= 1;
		end
	end
	
	assign high = 1;
	assign gnd = 0;
	
endmodule