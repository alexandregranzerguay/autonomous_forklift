// Initial attempt at stepper motor control
module Clock_Divider(input clk, input reset_reset_n, output reg clk_div);
	
	localparam cTime = 100000000;
	reg [31:0] count;
	
	// Set the clock output
	always @(posedge clk or negedge reset_reset_n) begin
		if (reset_reset_n == 0) begin
			clk_div <= 0;
			count = 32'b0;
		end
		else begin
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
endmodule