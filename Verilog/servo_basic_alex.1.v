// Initial attempt at stepper motor control
module servo_basic(input clock_clk, input reset_low, output reg pwm_out, output high, output gnd);
	reg next_out;
	reg [31:0] count;
	
	localparam totalTime = 100000000;
	localparam halfTime = 70000000;
	
    //50% Duty Cycle
	always @(count) begin
		if (count > halfTime) begin
			pwm_out <= 0;
		end
		else begin
			pwm_out <= 1;
		end
	end
	
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

    // Constant High and Low
	assign high = 1;
	assign gnd = 0;
	
endmodule