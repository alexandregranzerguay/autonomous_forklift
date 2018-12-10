// Initial attempt at stepper motor control
module stepper_control(input clock_clk, input reset_low, output reg [5:0] state_out);	
	reg [5:0] next_out;
	
	// Move FSM when clock cycles
	always @(clock_clk or reset_low) begin
		if (reset_low == 0) begin
			next_out <= 6'b000000;
		end
		else if (clock_clk == 1) begin
			// Determine next state to use
			next_out <= 6'b000000;
			case(state_out)
				6'b000000 : next_out <= 6'b11zzz0;
				6'b11zzz0 : next_out <= 6'b11zz0z;
				6'b11zz0z : next_out <= 6'b11z0zz;
				6'b11z0zz : next_out <= 6'b110zzz;
				6'b110zzz : next_out <= 6'b11zzz0;
			endcase
		end
		state_out <= next_out;
	end
	
endmodule