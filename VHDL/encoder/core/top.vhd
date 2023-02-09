-----------------------------------------------------------------------------------------------------
-- Name: Wesley Grignani
-- Laboratory of Embedded and Distributed Systems (LEDS) - UNIVALI
-----------------------------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
library work;
use work.ccsds123_B2_package.all;

entity top is
  port ( i_clk              : in  std_logic;
         i_rst              : in  std_logic;
         i_start            : in  std_logic;
         i_t                : in  std_logic_vector(7 downto 0); 
         i_z                : in  std_logic_vector(2 downto 0); 
         i_mapped           : in  std_logic_vector(15 downto 0);
         o_encoded          : out std_logic_vector(31 downto 0); 
         o_out_bits_written : out std_logic_vector(5 downto 0);
         o_valid            : out std_logic);
end top;

architecture Behavioral of top is

component control is
  port (i_clk                : in  std_logic;
        i_rst                : in  std_logic;
        i_start              : in  std_logic;
        i_uz                 : in  std_logic_vector(KZ_SIZE-1 downto 0); -- vem do datapath
        i_t                  : in  std_logic_vector(7 downto 0); -- vem do datapath
        i_z                  : in  std_logic_vector(2 downto 0); -- vem do datapath
        o_en_samples         : out std_logic;  -- habilita registrador pra guardar mapped, i_z e i_t da amostra a ser codificada
        o_en_mem_init        : out std_logic;  -- habilita inicialização das memorias
        o_sel_muxs           : out std_logic;
        o_sel_muxs_encoded   : out std_logic_vector(1 downto 0);
        o_en_count_reg       : out std_logic_vector(4 downto 0);
        o_en_acc_reg         : out std_logic_vector(4 downto 0);
        o_en_encode_mapped   : out std_logic;  -- habilita calculo da codificacao da amostra com signal
        o_en_calc_kz_uz      : out std_logic;  -- habiita calculo de kz e uz
        o_en_encode_uzkz     : out std_logic;  -- habilita calculo da codificacao da amostra com kz e uz
        o_en_encode_umax     : out std_logic;  -- habilita calculo da codificacao da amostra com umax
        o_en_att_mem         : out std_logic;  -- habilita atualizacao das memorias
        o_valid              : out std_logic); 
end component;

component datapath is
  port ( i_clk                : in  std_logic;  -- clock
         i_sel_muxs           : in  std_logic;  -- seletor do multiplexador dos registradores acumulador entre init e update
         i_sel_muxs_encoded   : in  std_logic_vector(1 downto 0); -- seletor do multiplexador de saida da codificação
         i_en_mem_init        : in  std_logic;  -- habilita inicialização das memorias
         i_en_samples         : in  std_logic;  -- habilita registrador pra guardar mapped, i_z e i_t da amostra a ser codificada
         i_en_encode_mapped   : in  std_logic;  -- habilita calculo da codificacao da amostra com signal
         i_en_calc_kz_uz      : in  std_logic;  -- habiita calculo de kz e uz
         i_en_encode_uzkz     : in  std_logic;  -- habilita calculo da codificacao da amostra com kz e uz
         i_en_encode_umax     : in  std_logic;  -- habilita calculo da codificacao da amostra com umax
         i_en_att_mem         : in  std_logic;  -- habilita atualizacao das memorias
         i_en_acc_reg         : in  std_logic_vector(4 downto 0);  -- habilita a escrita nos registradores acumulador
         i_en_count_reg       : in  std_logic_vector(4 downto 0);  -- habilita a escrita nos registradores contador
         i_t                  : in  std_logic_vector(7 downto 0);  -- valor de entrada da amostra atual
         i_z                  : in  std_logic_vector(2 downto 0);  -- valor de entrada da amostra atual
         i_mapped             : in  std_logic_vector(15 downto 0); -- valor de entrada da amostra atual
         o_t                  : out std_logic_vector(7 downto 0);  -- valor de t proveniente do registrador i_t para utilizar no controle
         o_uz                 : out std_logic_vector(KZ_SIZE-1 downto 0);  -- valor de u_z de saida do calculo de uz_kz
         o_z                  : out std_logic_vector(2 downto 0); -- valor de z para utilizar no controle
         o_out_encoded        : out std_logic_vector(31 downto 0); -- saida de codificação
         o_out_bits_written   : out std_logic_vector(5 downto 0)); -- quantidade de bits escritos/utilizados da saida de 32 bits
end component;

signal w_en_samples, w_en_mem_init, w_en_encode_mapped, w_en_calc_kz_uz, w_en_encode_uzkz, w_en_encode_umax, w_en_att_mem, w_sel_muxs : std_logic := '0';
signal w_en_count_reg, w_en_acc_reg : std_logic_vector(4 downto 0) := (others => '0');
signal w_sel_muxs_encoded : std_logic_vector(1 downto 0) := (others => '0');

signal w_uz : std_logic_vector(KZ_SIZE-1 downto 0); -- vem do datapath
signal w_t : std_logic_vector(7 downto 0); -- vem do datapath
signal w_z : std_logic_vector(2 downto 0); -- vem do datapath

begin

    u_control : control 
      port map (i_clk                => i_clk,
                i_rst                => i_rst,
                i_start              => i_start,
                i_uz                 => w_uz,
                i_t                  => w_t,
                i_z                  => w_z,
                o_en_samples         => w_en_samples,
                o_en_mem_init        => w_en_mem_init,
                o_sel_muxs           => w_sel_muxs,
                o_sel_muxs_encoded   => w_sel_muxs_encoded,
                o_en_count_reg       => w_en_count_reg,
                o_en_acc_reg         => w_en_acc_reg,
                o_en_encode_mapped   => w_en_encode_mapped,
                o_en_calc_kz_uz      => w_en_calc_kz_uz,
                o_en_encode_uzkz     => w_en_encode_uzkz,
                o_en_encode_umax     => w_en_encode_umax,
                o_en_att_mem         => w_en_att_mem,
                o_valid              => o_valid);
            
  u_datapath : datapath
  port map ( i_clk                => i_clk,
             i_sel_muxs           => w_sel_muxs,
             i_sel_muxs_encoded   => w_sel_muxs_encoded,
             i_en_mem_init        => w_en_mem_init,
             i_en_samples         => w_en_samples,
             i_en_encode_mapped   => w_en_encode_mapped,
             i_en_calc_kz_uz      => w_en_calc_kz_uz,
             i_en_encode_uzkz     => w_en_encode_uzkz,
             i_en_encode_umax     => w_en_encode_umax,
             i_en_att_mem         => w_en_att_mem,
             i_en_acc_reg         => w_en_acc_reg,
             i_en_count_reg       => w_en_count_reg,
             i_t                  => i_t,
             i_z                  => i_z,
             i_mapped             => i_mapped,
             o_t                  => w_t,
             o_uz                 => w_uz, 
             o_z                  => w_z,
             o_out_encoded        => o_encoded,
             o_out_bits_written   => o_out_bits_written);

end Behavioral;
