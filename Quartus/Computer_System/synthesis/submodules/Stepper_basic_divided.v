// Initial attempt at stepper motor control
module stepper_control_divided(input clock_clk, input reset_low, output reg [5:0] state_out);
	//reg clk_div;
	reg [5:0] next_out;
	reg [31:0] count;
	
	localparam cTime = 100000000;
	
	// Move FSM when clock cycles
	always @(clock_clk or reset_low) begin
		if (reset_low == 0) begin
			next_out <= 6'b000000;
			//clk_div <= 0;
			count <= 32'b0;
		end
		else if (count == cTime - 1) begin
			count <= 32'b0;
			//clk_div <= ~clk_div;
			// Determine next state to use
			next_out <= 6'b000000;
			case(state_out)
				6'b000000 : next_out <= 6'b11zzz0;
				6'b11zzz0 : next_out <= 6'b11zz0z;
				6'b11zz0z : next_out <= 6'b11z0zz;
				6'b11z0zz : next_out <= 6'b110zzz;
				6'b110zzz : next_out <= 6'b11zzz0;
				
			endcase
			state_out <= next_out;
		end
		else if (clock_clk == 1) begin
			//clk_div <= clk_div;
			count <= count + 1;
		end
	end
	
	//always @(negedge reset_low) begin
	//	if (reset_low == 0) begin
	//		next_out <= 6'b000000;
	//		//clk_div <= 0;
	//		count <= 32'b0;
	//	end
	//end
	
	//always @(posedge clk_div) begin
	//	// Determine next state to use
	//	case(state_out)
	//		6'b000000 : next_out <= 6'b11zzz0;
	//		6'b11zzz0 : next_out <= 6'b11zz0z;
	//		6'b11zz0z : next_out <= 6'b11z0zz;
	//		6'b11z0zz : next_out <= 6'b110zzz;
	//		6'b110zzz : next_out <= 6'b11zzz0;
	//	endcase
	//	state_out <= next_out;
	//end
	
endmodule