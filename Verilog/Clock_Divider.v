// Initial attempt at stepper motor control
module clock_divider(input clk, input reset_reset_n, output reg clk_div);
	localparam cTime = 100000000;
	
	reg [31:0] count;
	
	// Set the clock output
	always @ (clk or reset_reset_n) begin
		if (reset_reset_n == 0) begin
			clk_div <= 0;
			count = 32'b0;
		end
		else if (clk == 1) begin
			if (count == cTime - 1) begin
				count = 32'b0;
				clk_div <= ~clk_div;
			end
			else begin
				//clk_div <= clk_div;
				count <= count + 1;
			end
		end
	end
	
	//always @(negedge reset_reset_n) begin
	//	if (reset_reset_n == 0) begin
	//		//clk_div <= 0;
	//		count = 32'b0;
	//	end
	//end
	
endmodule