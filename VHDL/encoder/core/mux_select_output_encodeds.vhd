-----------------------------------------------------------------------------------------------------
-- Name: Wesley Grignani
-- Laboratory of Embedded and Distributed Systems (LEDS) - UNIVALI
-----------------------------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
library work;
use work.ccsds123_B2_package.all;

entity mux_select_output_encodeds is
  port (i_uzkz_encoded    : in  std_logic_vector(15 downto 0);
        i_umax_encoded    : in  std_logic_vector(31 downto 0);
        i_dmapped_encoded : in  std_logic_vector(15 downto 0);
        i_sel             : in  std_logic_vector(1 downto 0);
        o_encoded_out     : out std_logic_vector(31 downto 0));
end mux_select_output_encodeds;

architecture Behavioral of mux_select_output_encodeds is
signal w_out_encoded : std_logic_vector(31 downto 0) := (others => '0');

begin
  p_mux : process(i_sel, i_dmapped_encoded, i_umax_encoded, i_uzkz_encoded)
  begin 
    case i_sel is 
      -- encoded uz_kz
      when "00"  => w_out_encoded(31 downto 16) <= (others => '0');
                    w_out_encoded(15 downto 0) <= i_uzkz_encoded;
      
      -- encoded umax
      when "01" => w_out_encoded <= i_umax_encoded;
      
      -- encoded dmapped
      when "10" => w_out_encoded(31 downto 16) <= (others => '0');
                   w_out_encoded(15 downto 0) <= i_dmapped_encoded;
      
      when others  => w_out_encoded <= (others => '0');
    
    end case;
  end process;
  
  o_encoded_out <= w_out_encoded;
  
end Behavioral;
