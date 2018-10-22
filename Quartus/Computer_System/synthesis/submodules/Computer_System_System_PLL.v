// Computer_System_System_PLL.v

// This file was auto-generated from altera_up_avalon_sys_sdram_pll_hw.tcl.  If you edit it your changes
// will probably be lost.
// 
// Generated using ACDS version 17.1 593

`timescale 1 ps / 1 ps
module Computer_System_System_PLL (
		input  wire  ref_clk_clk,        //      ref_clk.clk
		input  wire  ref_reset_reset,    //    ref_reset.reset
		output wire  sys_clk_clk,        //      sys_clk.clk
		output wire  reset_source_reset  // reset_source.reset
	);

	wire    sys_pll_locked_export; // sys_pll:locked -> reset_from_locked:locked

	Computer_System_System_PLL_sys_pll sys_pll (
		.refclk   (ref_clk_clk),           //  refclk.clk
		.rst      (ref_reset_reset),       //   reset.reset
		.outclk_0 (sys_clk_clk),           // outclk0.clk
		.outclk_1 (),                      // outclk1.clk
		.locked   (sys_pll_locked_export)  //  locked.export
	);

	altera_up_avalon_reset_from_locked_signal reset_from_locked (
		.reset  (reset_source_reset),    // reset_source.reset
		.locked (sys_pll_locked_export)  //       locked.export
	);

endmodule
