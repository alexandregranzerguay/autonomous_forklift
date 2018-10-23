// Initial attempt at stepper motor control
module stepper_control(clk, motor_enable, direction, out);
	// Define inputs and outputs
	input clk; // Clock input to drive finite state machine
	input motor_enable; // 1 is motor on, 0 is motor off
	input direction; // Bit telling motor direction to move - 0 is clockwise, 1 is counter-clockwise
	output [3:0] out; // Output to pins connected to motor (4 for now, 6 if possible/necessary)
	
	reg [3:0] out;
	reg [3:0] next_out;
	
	// Move FSM when clock cycles
	always @(posedge clk) begin
		// Check if motor is enabled
		if (motor_enable) begin
			// Check which direction is specified
			if (direction) begin
				// Determine next state to use
				case(out)
					4'b0000 : next_out = 4'b0001;
					4'b0001 : next_out = 4'b0011;
					4'b0011 : next_out = 4'b0010;
					4'b0010 : next_out = 4'b0110;
					4'b0110 : next_out = 4'b0100;
					4'b0100 : next_out = 4'b1100;
					4'b1100 : next_out = 4'b1000;
					4'b1000 : next_out = 4'b1001;
					4'b1001 : next_out = 4'b0001;
				endcase
			end
			else begin
				// Determine next state to use
				case(out)
					4'b0000 : next_out = 4'b1000;
					4'b1000 : next_out = 4'b1100;
					4'b1100 : next_out = 4'b0100;
					4'b0100 : next_out = 4'b0110;
					4'b0110 : next_out = 4'b0010;
					4'b0010 : next_out = 4'b0011;
					4'b0011 : next_out = 4'b0001;
					4'b0001 : next_out = 4'b1001;
					4'b1001 : next_out = 4'b1000;
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