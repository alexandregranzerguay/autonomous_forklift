// Initial attempt at stepper motor control
module test_bench;

	reg clk, reset_n;
	wire pwm_left_out;
	wire pwm_right_out;
	wire pwm_lift_out;
	reg [31:0] pulseTimeLeft;
	reg [31:0] pulseTimeRight;
	reg [31:0] pulseTimeLift;
	reg read_left;
	reg read_right;
	reg write_left;
	reg write_right;
	reg write_lift;
	reg cs_left;
	reg cs_right;
	reg cs_lift;
	wire [31:0] readdata_left;
	wire [31:0] readdata_right;
	reg pwm_response_left;
	reg pwm_response_right;
	
	always begin
		# 0.5
		clk <= !clk;
	end
	
	initial begin
		clk <= 1;
		pulseTimeLeft <= 3;
		read_left <= 0;
		write_left <= 0;
		cs_left <= 0;
		pwm_response_left <= 1;
		pulseTimeRight <= 2;
		read_right <= 0;
		write_right <= 0;
		cs_right <= 0;
		pwm_response_right <= 0;
		pulseTimeLift <= 4;
		write_lift <= 0;
		cs_lift <= 0;
		reset_n <= 1;
		# 10
		reset_n <= 0;
		# 10
		reset_n <= 1;
		
		// Test left servo
		cs_left <= 1;
		write_left <= 1;
		# 5
		write_left <= 0;
		# 1
		read_left <= 1;
		# 3
		pwm_response_left <= 0;
		read_left <= 0;
		# 10
		read_left <= 1;
		pwm_response_left <= 1;
		# 40
		pwm_response_left <= 0;
		# 10
		read_left <= 0;
		write_left <= 1;
		pulseTimeLeft <= 5;
		# 4
		write_left <= 0;
		cs_left <= 0;
		
		// Test right servo
		cs_right <= 1;
		write_right <= 1;
		# 5
		write_right <= 0;
		# 1
		read_right <= 1;
		# 3
		pwm_response_right <= 0;
		read_right <= 0;
		# 10
		read_right <= 1;
		pwm_response_right <= 1;
		# 40
		pwm_response_right <= 0;
		# 10
		read_right <= 0;
		write_right <= 1;
		pulseTimeRight <= 5;
		# 4
		write_right <= 0;
		cs_right <= 0;
		
		// Test lift servo
		cs_lift <= 1;
		write_lift <= 1;
		# 5
		write_lift <= 0;
		# 40
		write_lift <= 1;
		pulseTimeLift <= 5;
		# 4
		write_lift <= 0;
		cs_lift <= 0;
		
	end
	
	servo_avalon servoLeft(clk, reset_n, read_left, write_left, cs_left, readdata_left, pulseTimeLeft, pwm_response_left, pwm_left_out);
	servo_avalon servoRight(clk, reset_n, read_right, write_right, cs_right, readdata_right, pulseTimeRight, pwm_response_right, pwm_right_out);
	servo_pos_avalon forklift(clk, reset_n, write_lift, cs_lift, pulseTimeLift, pwm_lift_out);
	
endmodule