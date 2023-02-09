-----------------------------------------------------------------------------------------------------
-- Name: Wesley Grignani
-- Laboratory of Embedded and Distributed Systems (LEDS) - UNIVALI
-----------------------------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
library work;
use work.ccsds123_B2_package.all;

entity mux_bits_written is
  port (i_bits_uzkz    : in  std_logic_vector(5 downto 0);
        i_bits_umax    : in  std_logic_vector(5 downto 0);
        i_bits_dmapped : in  std_logic_vector(5 downto 0);
        i_sel          : in  std_logic_vector(1 downto 0);
        o_bits_written : out std_logic_vector(5 downto 0));
end mux_bits_written;

architecture Behavioral of mux_bits_written is
begin

  p_mux : process(i_sel, i_bits_dmapped, i_bits_umax, i_bits_uzkz)
  begin 
    case i_sel is 
      when "00"  => o_bits_written <= i_bits_uzkz;
      when "01"  => o_bits_written <= i_bits_umax;
      when "10"  => o_bits_written <= i_bits_dmapped;
      when others => o_bits_written <= (others => '0');
    end case;
  end process p_mux;

end Behavioral;
