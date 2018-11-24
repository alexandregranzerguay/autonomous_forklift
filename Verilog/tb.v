// Initial attempt at stepper motor control
module test_bench;

	reg clk, reset_n;
	wire [5:0] state_out;
	wire [5:0] state_out_div;
	wire clk_div;
	always begin
		# 0.5
		clk <= !clk;
	end
	
	initial begin
		clk <= 0;
		reset_n <= 1;
		# 10
		reset_n <= 0;
		# 10
		reset_n <= 1;
	end
	
	clock_divider ck_div(clk, reset_n, clk_div);
	
	stepper_control stepper(clk_div, reset_n, state_out);
	
	stepper_control_divided stepper_div(clk, reset_n, state_out_div);
	
endmodule