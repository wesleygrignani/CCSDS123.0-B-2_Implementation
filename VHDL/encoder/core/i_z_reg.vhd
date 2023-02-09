-----------------------------------------------------------------------------------------------------
-- Name: Wesley Grignani
-- Laboratory of Embedded and Distributed Systems (LEDS) - UNIVALI
-----------------------------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
library work;
use work.ccsds123_B2_package.all;

entity i_z_reg is
  port (i_clk : in  std_logic;
        i_en  : in  std_logic;
        i_z   : in  std_logic_vector(2 downto 0);
        o_z   : out std_logic_vector(2 downto 0));
end i_z_reg;

architecture Behavioral of i_z_reg is
signal w_z : std_logic_vector(2 downto 0) := (others => '0');
begin
  
  process(i_clk, i_en)
  begin 
    if(rising_edge(i_clk) and i_en = '1') then
      w_z <= i_z;
    end if;
  end process;
  
  o_z <= w_z;

end Behavioral;
