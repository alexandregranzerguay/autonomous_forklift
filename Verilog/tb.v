// Initial attempt at stepper motor control
module test_bench;

	reg clk, reset_n;
	wire pwm_out;
	reg [31:0] pulseTime;
	reg read;
	reg write;
	reg cs;
	wire [31:0] readdata;
	reg pwm_response;
	
	always begin
		# 0.5
		clk <= !clk;
	end
	
	initial begin
		clk <= 0;
		pulseTime <= 3;
		read <= 0;
		write <= 0;
		cs <= 0;
		pwm_response <= 1;
		reset_n <= 1;
		# 10
		reset_n <= 0;
		# 10
		reset_n <= 1;
		
		cs <= 1;
		write <= 1;
		# 5
		write <= 0;
		# 1
		read <= 1;
		# 3
		pwm_response <= 0;
		read <= 0;
		# 10
		read <= 1;
		
		
		
	end
	
	servo_avalon servo(clk, reset_n, read, write, cs, readdata, pulseTime, pwm_response, pwm_out);
	
endmodule