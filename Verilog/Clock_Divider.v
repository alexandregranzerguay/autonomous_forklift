// Initial attempt at stepper motor control
module stepper_control(clk, reset, clk_div);
	// Define inputs and outputs
	input clk; // Raw clock input
	input reset; // Reset
	output reg clk_div; // Divided clock signal
	
	localparam cTime = 10000000;
	
	reg [31:0] count;
	
	// Increment the count and reset when too high
	always @ (posedge(clk), posedge(reset))
	begin
		if (reset == 1'b1)
			count <= 32'b0;
		else if (count == cTime - 1)
			count <= 32'b0;
		else
			count <= count + 1;
	end
	
	// Set the clock output
	always @ (posedge(clk), posedge(reset))
	begin
		if (reset == 1'b1)
			clk_div <= 1'b0;
		else if (count == cTime - 1)
			clk_div <= ~clk_div;
		else
			clk_div <= clk_div;
	end
	
endmodule