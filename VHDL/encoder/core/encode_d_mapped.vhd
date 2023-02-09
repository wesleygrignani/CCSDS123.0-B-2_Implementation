-----------------------------------------------------------------------------------------------------
-- Name: Wesley Grignani
-- Laboratory of Embedded and Distributed Systems (LEDS) - UNIVALI
-----------------------------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
library work;
use work.ccsds123_B2_package.all;

entity encode_d_mapped is
  port (i_clk          : in  std_logic;
        i_en           : in  std_logic;
        i_mapped       : in  std_logic_vector(15 downto 0);
        o_encode       : out std_logic_vector(15 downto 0);
        o_bits_written : out std_logic_vector(5 downto 0));
end encode_d_mapped;

architecture Behavioral of encode_d_mapped is
signal w_encode : std_logic_vector(15 downto 0) := (others => '0');

begin
  process(i_clk, i_en)
  begin
    if(rising_edge(i_clk) and i_en = '1') then
      w_encode <= i_mapped;
    end if;
  end process;
  o_encode <= w_encode;
  o_bits_written <= std_logic_vector(to_unsigned(16, 6));
end Behavioral;
