-----------------------------------------------------------------------------------------------------
-- Name: Wesley Grignani
-- Laboratory of Embedded and Distributed Systems (LEDS) - UNIVALI
-----------------------------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity mapped_reg is
  port (i_clk      : in  std_logic;
        i_en       : in  std_logic;
        i_mapped   : in  std_logic_vector(15 downto 0);
        o_mapped   : out std_logic_vector(15 downto 0));
end mapped_reg;

architecture Behavioral of mapped_reg is
signal w_mapped : std_logic_vector(15 downto 0) := (others => '0');
begin
  
  process(i_clk, i_en)
  begin 
    if(rising_edge(i_clk) and i_en = '1') then
      w_mapped <= i_mapped;
    end if;
  end process;
  
  o_mapped <= w_mapped;
  
end Behavioral;
