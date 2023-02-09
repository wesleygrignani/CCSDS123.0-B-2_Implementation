-----------------------------------------------------------------------------------------------------
-- Name: Wesley Grignani
-- Laboratory of Embedded and Distributed Systems (LEDS) - UNIVALI
-----------------------------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
library work;
use work.ccsds123_B2_package.all;

entity mux_count_for_kzcalc is
  Port (i_count0 : in  std_logic_vector(COUNT_SIZE-1 downto 0);
        i_count1 : in  std_logic_vector(COUNT_SIZE-1 downto 0);
        i_count2 : in  std_logic_vector(COUNT_SIZE-1 downto 0);
        i_count3 : in  std_logic_vector(COUNT_SIZE-1 downto 0);
        i_count4 : in  std_logic_vector(COUNT_SIZE-1 downto 0);
        i_sel    : in  std_logic_vector(2 downto 0);
        o_out    : out std_logic_vector(COUNT_SIZE-1 downto 0));
end mux_count_for_kzcalc;

architecture Behavioral of mux_count_for_kzcalc is

begin

  p_mux : process(i_sel, i_count0, i_count1, i_count2, i_count3, i_count4)
  begin 
    case i_sel is 
      when "000"  => o_out <= i_count0;
      when "001"  => o_out <= i_count1;
      when "010"  => o_out <= i_count2;
      when "011"  => o_out <= i_count3;
      when "100"  => o_out <= i_count4;
      when others => o_out    <= (others => '0');
    end case;
  end process p_mux;

end Behavioral;
