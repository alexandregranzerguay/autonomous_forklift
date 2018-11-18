library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;
use IEEE.numeric_std.all;

entity my_counter is
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
end entity my_counter;

architecture rtl of my_counter is

signal count : std_logic_vector(31 downto 0);
signal load_enable : std_logic;

begin
the_count : process (clock_clk, reset_reset_n)
begin
	if (reset_reset_n = '0') then
		count <= (others => '0');
	elsif (rising_edge(clock_clk)) then
		if (load_enable = '1') then
			count <= count + 1;
		end if;
	end if;
end process;

the_load_enable : process (clock_clk, reset_reset_n)
begin
	if (reset_reset_n = '0') then
		load_enable <= '0';
	elsif (rising_edge(clock_clk)) then
		if (avalon_slave_chipselect = '1' and avalon_slave_address = '1' and avalon_slave_write = '1') then
			load_enable <= load_enable xor '1';
		end if;
	end if;
end process;

avalon_slave_readdata <= count;

end architecture;