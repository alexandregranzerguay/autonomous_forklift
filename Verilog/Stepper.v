// Initial attempt at stepper motor control
module stepper_control(clk, motor_enable, reset_low, direction, out);
	// Define inputs and outputs
	input clk; // Clock input to drive finite state machine
	input motor_enable; // 1 is motor on, 0 is motor off
	input reset_low; // active-low reset
	input direction; // Bit telling motor direction to move - 0 is clockwise, 1 is counter-clockwise
	output [5:0] out; // Output to pins connected to motor (4 for now, 6 if possible/necessary)
	
	reg [5:0] out;
	reg [5:0] next_out;
	
	// Move FSM when clock cycles
	always @(posedge clk) begin
		if (reset_low == 0) begin
			next_out = 6'b000000;
		end
		// Check if motor is enabled
		if (motor_enable) begin
			// Check which direction is specified
			if (direction) begin
				// Determine next state to use
				case(out)
					6'b000000 : next_out = 6'b11zzz0;
					6'b11zzz0 : next_out = 6'b11zz0z;
					6'b11zz0z : next_out = 6'b11z0zz;
					6'b11z0zz : next_out = 6'b110zzz;
					6'b110zzz : next_out = 6'b11zzz0;
				endcase
			end
			else begin
				// Determine next state to use
				case(out)
					6'b000000 : next_out = 6'b110zzz;
					6'b110zzz : next_out = 6'b11z0zz;
					6'b11z0zz : next_out = 6'b11zz0z;
					6'b11zz0z : next_out = 6'b11zzz0;
					6'b11zzz0 : next_out = 6'b110zzz;
				endcase
			end
		end
		else begin
			// Turn off motor
			next_out = 4'b0000;
		end
		out = next_out;
	end
	
endmodule