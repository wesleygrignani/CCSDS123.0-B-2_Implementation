-----------------------------------------------------------------------------------------------------
-- Name: Wesley Grignani
-- Laboratory of Embedded and Distributed Systems (LEDS) - UNIVALI
-----------------------------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
library work;
use work.ccsds123_B2_package.all;

entity encode_umax is
  port (i_clk          : in  std_logic;
        i_en           : in  std_logic;
        i_mapped       : in  std_logic_vector(15 downto 0);
        o_encode       : out std_logic_vector(31 downto 0);
        o_bits_written : out std_logic_vector(5 downto 0));
end encode_umax;

architecture Behavioral of encode_umax is
begin

  process(i_clk, i_en)
  begin
    if(rising_edge(i_clk) and i_en = '1') then 
      o_encode(31 downto 16) <= (others => '0');
      o_encode(15 downto 0) <= i_mapped;
    end if;
  end process;
 
  o_bits_written <= std_logic_vector(to_unsigned(UMAX+16 , 6));
  
end Behavioral;
