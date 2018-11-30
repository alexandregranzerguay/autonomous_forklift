// Initial attempt at stepper motor control
module test_bench;

	reg clk, reset_n;
	wire pwm_out;
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
	
	servo_basic servo(clk, reset_n, pwm_out);
	
endmodule