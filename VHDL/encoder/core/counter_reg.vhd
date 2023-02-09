-----------------------------------------------------------------------------------------------------
-- Name: Wesley Grignani
-- Laboratory of Embedded and Distributed Systems (LEDS) - UNIVALI
-----------------------------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
library work;
use work.ccsds123_B2_package.all;

entity counter_reg is
  Port ( i_clk    : in  std_logic;
         i_en     : in  std_logic;
         i_count  : in  std_logic_vector(COUNT_SIZE-1 downto 0);
         o_count  : out std_logic_vector(COUNT_SIZE-1 downto 0));
end counter_reg;

architecture Behavioral of counter_reg is
begin

  process(i_clk, i_en)
  begin 
    if(rising_edge(i_clk) and i_en = '1') then
      o_count <= i_count;
    end if;
  end process;

end Behavioral;
