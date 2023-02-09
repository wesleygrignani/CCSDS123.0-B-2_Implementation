-----------------------------------------------------------------------------------------------------
-- Name: Wesley Grignani
-- Laboratory of Embedded and Distributed Systems (LEDS) - UNIVALI
-----------------------------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
library work;
use work.ccsds123_B2_package.all;

entity encode_uzkz is
  port (i_clk          : in  std_logic;
        i_en           : in  std_logic;
        i_kz           : in  std_logic_vector(KZ_SIZE-1 downto 0);
        i_uz           : in  std_logic_vector(KZ_SIZE-1 downto 0);
        i_mapped       : in  std_logic_vector(15 downto 0); 
        o_encode       : out std_logic_vector(15 downto 0);
        o_bits_written : out std_logic_vector(5 downto 0));
end encode_uzkz;

architecture Behavioral of encode_uzkz is
signal w_kz, w_uz, w_bits_written : integer := 0;
signal w_encode : std_logic_vector(15 downto 0) := (others => '0');
begin
  w_kz <= to_integer(unsigned(i_kz));
  w_uz <= to_integer(unsigned(i_uz));
   
  process(i_clk, i_en)
  begin
    if(rising_edge(i_clk) and i_en = '1') then
      w_encode(w_kz-1 downto 0) <= i_mapped(w_kz-1 downto 0);
      w_encode(w_kz) <= '1';
      w_encode(w_kz+w_uz downto w_kz+1) <= (others => '0');
      w_bits_written <= w_kz+w_uz+1;
    end if;
  end process;
  
  o_encode <= w_encode;
  o_bits_written <= std_logic_vector(to_unsigned(w_bits_written, 6));
  
end Behavioral;
