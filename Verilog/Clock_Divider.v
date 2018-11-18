// Initial attempt at stepper motor control
module stepper_control(input clk, input reset_reset_n, output reg clk_div);
	localparam cTime = 10000000;
	
	reg [31:0] count;
	
	// Increment the count and reset when too high
	always @ (posedge(clk))
	begin
		if (reset_reset_n == 1'b0)
			count <= 32'b0;
		else if (count == cTime - 1)
			count <= 32'b0;
		else
			count <= count + 1;
	end
	
	// Set the clock output
	always @ (posedge(clk))
	begin
		if (reset_reset_n == 1'b0)
			clk_div <= 1'b0;
		else if (count == cTime - 1)
			clk_div <= ~clk_div;
		else
			clk_div <= clk_div;
	end
	
endmodule