library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;
use IEEE.numeric_std.all;

entity out_test is
	port (
		clock_clk					: in	std_logic			:= '0';
		reset_reset_n				: in	std_logic			:= '0';
		avalon_slave_address		: in	std_logic			:= '0';
		avalon_slave_chipselect		: in	std_logic			:= '0';
		avalon_slave_read			: in	std_logic			:= '0';
		avalon_slave_write			: in	std_logic			:= '0';
		avalon_slave_readdata		: out	std_logic_vector(31 downto 0);
		avalon_slave_writedata		: in	std_logic_vector(31 downto 0) := (others => '0')
	);
end entity out_test;

architecture rtl of out_test is

signal count : std_logic_vector(31 downto 0);

begin

read_test : process (avalon_slave_write)
begin
	if (avalon_slave_write = '0') then
		count <= "00000000000000000000000000001010";
	else 
		count <= "00000000000000000000000000000101";
	end if;
end process;

avalon_slave_readdata <= count;

end architecture;