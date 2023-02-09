-----------------------------------------------------------------------------------------------------
-- Name: Wesley Grignani
-- Laboratory of Embedded and Distributed Systems (LEDS) - UNIVALI
-----------------------------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
library work;
use work.ccsds123_B2_package.all;

entity datapath is
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
end datapath;

architecture Behavioral of datapath is

-- registers i_t, i_z e i_mapped samples to store
component i_t_reg is
  port (i_clk : in  std_logic;
        i_en  : in  std_logic;
        i_t   : in  std_logic_vector(7 downto 0);
        o_t   : out std_logic_vector(7 downto 0));
end component;

component i_z_reg is
  port (i_clk : in  std_logic;
        i_en  : in  std_logic;
        i_z   : in  std_logic_vector(2 downto 0);
        o_z   : out std_logic_vector(2 downto 0));
end component;

component mapped_reg is
  port (i_clk      : in  std_logic;
        i_en       : in  std_logic;
        i_mapped   : in  std_logic_vector(15 downto 0);
        o_mapped  : out std_logic_vector(15 downto 0));
end component;

-- memory counter and accumulator
component acc_reg is
  port ( i_clk  : in  std_logic;
         i_en   : in  std_logic;
         i_acc  : in  std_logic_vector(ACC_SIZE-1 downto 0);
         o_acc  : out std_logic_vector(ACC_SIZE-1 downto 0));
end component;

component counter_reg is
  Port ( i_clk    : in  std_logic;
         i_en     : in  std_logic;
         i_count  : in  std_logic_vector(COUNT_SIZE-1 downto 0);
         o_count  : out std_logic_vector(COUNT_SIZE-1 downto 0));
end component;

-- inicialização das memorias
component mem_init is
  port (i_clk         : in  std_logic; -- clock
        i_en          : in  std_logic; -- enable
        o_acc_value   : out std_logic_vector(ACC_SIZE-1 downto 0);    -- valor que sera inicializado em todos os reg acc
        o_count_value : out std_logic_vector(COUNT_SIZE-1 downto 0)); -- valor que sera inicializado em todos os reg acc
end component;

-- mux para os reg contador
component mux_count is
  Port ( i_count_from_init   : in  std_logic_vector(COUNT_SIZE-1 downto 0);
         i_count_from_update : in  std_logic_vector(COUNT_SIZE-1 downto 0);
         i_sel               : in  std_logic;
         o_count_out_mux     : out std_logic_vector(COUNT_SIZE-1 downto 0));
end component;

-- mux para os reg acumulador
component mux_acc is
  port ( i_acc_from_init   : in  std_logic_vector(ACC_SIZE-1 downto 0);
         i_acc_from_update : in  std_logic_vector(ACC_SIZE-1 downto 0);
         i_sel             : in  std_logic;
         o_acc_out_mux     : out std_logic_vector(ACC_SIZE-1 downto 0));
end component;

component update_acc_count is
  port ( i_clk       : in  std_logic;
         i_en        : in  std_logic;
         i_z         : in  std_logic_vector(2 downto 0);
         i_acc0      : in  std_logic_vector(ACC_SIZE-1 downto 0);
         i_acc1      : in  std_logic_vector(ACC_SIZE-1 downto 0);
         i_acc2      : in  std_logic_vector(ACC_SIZE-1 downto 0);
         i_acc3      : in  std_logic_vector(ACC_SIZE-1 downto 0);
         i_acc4      : in  std_logic_vector(ACC_SIZE-1 downto 0);
         i_count0    : in  std_logic_vector(COUNT_SIZE-1 downto 0);
         i_count1    : in  std_logic_vector(COUNT_SIZE-1 downto 0);
         i_count2    : in  std_logic_vector(COUNT_SIZE-1 downto 0);
         i_count3    : in  std_logic_vector(COUNT_SIZE-1 downto 0);
         i_count4    : in  std_logic_vector(COUNT_SIZE-1 downto 0);
         i_mapped    : in  std_logic_vector(15 downto 0);
         o_new_acc   : out std_logic_vector(ACC_SIZE-1 downto 0);
         o_new_count : out std_logic_vector(COUNT_SIZE-1 downto 0));
end component;

-- calculo da variavel kz e uz 
component kz_calc is
  port ( i_clk       : in  std_logic;
         i_en        : in  std_logic;
         i_acc_reg   : in  std_logic_vector(ACC_SIZE-1 downto 0);
         i_count_reg : in  std_logic_vector(COUNT_SIZE-1 downto 0);
         i_mapped    : in  std_logic_vector(15 downto 0);
         o_kz        : out std_logic_vector(KZ_SIZE-1 downto 0);
         o_uz        : out std_logic_vector(KZ_SIZE-1 downto 0)); 
end component;

-- multiplexador dos acumuladores para o kz_calc
component mux_acc_for_kzcalc is
  Port (i_acc0 : in  std_logic_vector(ACC_SIZE-1 downto 0);
        i_acc1 : in  std_logic_vector(ACC_SIZE-1 downto 0);
        i_acc2 : in  std_logic_vector(ACC_SIZE-1 downto 0);
        i_acc3 : in  std_logic_vector(ACC_SIZE-1 downto 0);
        i_acc4 : in  std_logic_vector(ACC_SIZE-1 downto 0);
        i_sel  : in  std_logic_vector(2 downto 0);
        o_out  : out std_logic_vector(ACC_SIZE-1 downto 0));
end component;

-- multiplexador dos contadores para o kz_calc
component mux_count_for_kzcalc is
  Port (i_count0 : in  std_logic_vector(COUNT_SIZE-1 downto 0);
        i_count1 : in  std_logic_vector(COUNT_SIZE-1 downto 0);
        i_count2 : in  std_logic_vector(COUNT_SIZE-1 downto 0);
        i_count3 : in  std_logic_vector(COUNT_SIZE-1 downto 0);
        i_count4 : in  std_logic_vector(COUNT_SIZE-1 downto 0);
        i_sel    : in  std_logic_vector(2 downto 0);
        o_out    : out std_logic_vector(COUNT_SIZE-1 downto 0));
end component;

-- codificação por uz e kz
component encode_uzkz is
  port (i_clk          : in  std_logic;
        i_en           : in  std_logic;
        i_kz           : in  std_logic_vector(KZ_SIZE-1 downto 0);
        i_uz           : in  std_logic_vector(KZ_SIZE-1 downto 0);
        i_mapped       : in  std_logic_vector(15 downto 0); 
        o_encode       : out std_logic_vector(15 downto 0);
        o_bits_written : out std_logic_vector(5 downto 0));
end component;

-- codificação por umax
component encode_umax is
  port (i_clk          : in  std_logic;
        i_en           : in  std_logic;
        i_mapped       : in  std_logic_vector(15 downto 0);
        o_encode       : out std_logic_vector(31 downto 0);
        o_bits_written : out std_logic_vector(5 downto 0));
end component;

-- codifica amostra original quanto t = 0
component encode_d_mapped is
  port (i_clk          : in  std_logic;
        i_en           : in  std_logic;
        i_mapped       : in  std_logic_vector(15 downto 0);
        o_encode       : out std_logic_vector(15 downto 0);
        o_bits_written : out std_logic_vector(5 downto 0));
end component;

-- mux para selecionar ao final a saida de codificação
component mux_select_output_encodeds is
  port (i_uzkz_encoded    : in  std_logic_vector(15 downto 0);
        i_umax_encoded    : in  std_logic_vector(31 downto 0);
        i_dmapped_encoded : in  std_logic_vector(15 downto 0);
        i_sel             : in  std_logic_vector(1 downto 0);
        o_encoded_out     : out std_logic_vector(31 downto 0));
end component;

component mux_bits_written is
  port (i_bits_uzkz    : in  std_logic_vector(5 downto 0);
        i_bits_umax    : in  std_logic_vector(5 downto 0);
        i_bits_dmapped : in  std_logic_vector(5 downto 0);
        i_sel          : in  std_logic_vector(1 downto 0);
        o_bits_written : out std_logic_vector(5 downto 0));
end component;

signal w_t : std_logic_vector(7 downto 0) := (others => '0');
signal w_mapped : std_logic_vector(15 downto 0) := (others => '0');
signal w_z : std_logic_vector(2 downto 0) := (others => '0');

-- registradores acumuladores
signal w_acc_mux0, w_acc_mux1, w_acc_mux2, w_acc_mux3, w_acc_mux4 : std_logic_vector(ACC_SIZE-1 downto 0) := (others => '0'); --saida do mux, entrada nos regs
signal w_acc_to_mux, w_acc_update_to_mux, w_acc_out_kz_calc : std_logic_vector(ACC_SIZE-1 downto 0) := (others => '0'); -- saida dos reg acc
signal w_acc0, w_acc1, w_acc2, w_acc3, w_acc4 : std_logic_vector(ACC_SIZE-1 downto 0) := (others => '0');
-- registradores contadores
signal w_count_mux0, w_count_mux1, w_count_mux2, w_count_mux3, w_count_mux4, w_count_to_mux : std_logic_vector(COUNT_SIZE-1 downto 0) := (others => '0'); --saida do mux, entrada nos regs
signal w_count_update_to_mux, w_count_out_kz_calc : std_logic_vector(COUNT_SIZE-1 downto 0) := (others => '0'); -- saida dos reg contador  
signal w_count0, w_count1, w_count2, w_count3, w_count4 : std_logic_vector(COUNT_SIZE-1 downto 0) := (others => '0');
-- kz e uz (uz retorna tambem para o controle pois é utilizado para uma verificação)
signal w_kz, w_uz : std_logic_vector(KZ_SIZE-1 downto 0) := (others => '0');

-- sinais para codificação de saida e bits_written
signal w_encoded_uzkz, w_encoded_dmapped  : std_logic_vector(15 downto 0) := (others => '0');
signal w_encoded_umax : std_logic_vector(31 downto 0) := (others => '0');
signal w_bits_written_encoded_uzkz, w_bits_written_encoded_umax, w_bits_written_encoded_dmapped, w_out_bitswritten : std_logic_vector(5 downto 0) := (others => '0');

signal w_out_encoded : std_logic_vector(31 downto 0) := (others => '0');

begin
  
  -- para os calculos que usam t, levam em consideracao w_t
  u_t_reg : i_t_reg
  port map (i_clk => i_clk,
            i_en  => i_en_samples,
            i_t   => i_t,
            o_t   => w_t);
  
  o_t <= w_t;
            
  -- para os calculos que usam z, levam em consideracao w_z          
  u_z_reg : i_z_reg
  port map(i_clk => i_clk,
           i_en  => i_en_samples,
           i_z   => i_z,
           o_z   => w_z);
  
  o_z <= w_z;
  
  -- para os calculos que usam mapped, levam em consideracao w_mapped          
  u_mapped_reg : mapped_reg
  port map(i_clk      => i_clk,
           i_en       => i_en_samples,
           i_mapped   => i_mapped,
           o_mapped   => w_mapped);
           
  -- registradores acumulador e seus multiplexadores
  u_acc_reg0 : acc_reg 
  port map ( i_clk  => i_clk,
             i_en   => i_en_acc_reg(0),
             i_acc  => w_acc_mux0,
             o_acc  => w_acc0);
             
  u_acc_reg1 : acc_reg 
  port map ( i_clk  => i_clk,
             i_en   => i_en_acc_reg(1),
             i_acc  => w_acc_mux0,
             o_acc  => w_acc1);
             
  u_acc_reg2 : acc_reg 
  port map ( i_clk  => i_clk,
             i_en   => i_en_acc_reg(2),
             i_acc  => w_acc_mux0,
             o_acc  => w_acc2);
                      
  u_acc_reg3 : acc_reg 
  port map ( i_clk  => i_clk,
             i_en   => i_en_acc_reg(3),
             i_acc  => w_acc_mux0,
             o_acc  => w_acc3);
             
  u_acc_reg4 : acc_reg 
  port map ( i_clk  => i_clk,
             i_en   => i_en_acc_reg(4),
             i_acc  => w_acc_mux0,
             o_acc  => w_acc4);
             
  u_acc_mux0 : mux_acc
  port map(i_acc_from_init   => w_acc_to_mux,
           i_acc_from_update => w_acc_update_to_mux,
           i_sel             => i_sel_muxs,
           o_acc_out_mux     => w_acc_mux0);
   
  -- registradores e multiplexadores do contador
  u_count_reg0 : counter_reg
  port map( i_clk    => i_clk,
            i_en     => i_en_count_reg(0),
            i_count  => w_count_mux0,
            o_count  => w_count0);
  
  u_count_reg1 : counter_reg
  port map( i_clk    => i_clk,
            i_en     => i_en_count_reg(1),
            i_count  => w_count_mux0,
            o_count  => w_count1);
  
  u_count_reg2 : counter_reg
  port map( i_clk    => i_clk,
            i_en     => i_en_count_reg(2),
            i_count  => w_count_mux0,
            o_count  => w_count2);
  
  u_count_reg3 : counter_reg
  port map( i_clk    => i_clk,
            i_en     => i_en_count_reg(3),
            i_count  => w_count_mux0,
            o_count  => w_count3);
  
  u_count_reg4 : counter_reg
  port map( i_clk    => i_clk,
            i_en     => i_en_count_reg(4),
            i_count  => w_count_mux0,
            o_count  => w_count4);
  
  u_count_mux0 : mux_count
  port map( i_count_from_init   => w_count_to_mux,
            i_count_from_update => w_count_update_to_mux,
            i_sel               => i_sel_muxs,
            o_count_out_mux     => w_count_mux0);
  
  
  -- inicializa memoria contador e acumulador       
  u_mem_init : mem_init 
  port map( i_clk         => i_clk, -- clock
            i_en          => i_en_mem_init, -- enable
            o_acc_value   => w_acc_to_mux,    -- valor que sera inicializado em todos os reg acc
            o_count_value => w_count_to_mux); -- valor que sera inicializado em todos os reg acc
         
  -- atualizador dos registradores acumulador e contador       
  u_update_acc_count : update_acc_count
  port map(i_clk       => i_clk,
           i_en        => i_en_att_mem,
           i_z         => w_z,
           i_acc0      => w_acc0,
           i_acc1      => w_acc1,
           i_acc2      => w_acc2,
           i_acc3      => w_acc3,
           i_acc4      => w_acc4,
           i_count0    => w_count0,
           i_count1    => w_count1,
           i_count2    => w_count2,
           i_count3    => w_count3,
           i_count4    => w_count4,
           i_mapped    => w_mapped,
           o_new_acc   => w_acc_update_to_mux,
           o_new_count => w_count_update_to_mux);
           
  -- multiplexador dos acumuludaores
  u_muxs_acc : mux_acc_for_kzcalc 
  port map (i_acc0 => w_acc0,
            i_acc1 => w_acc1,
            i_acc2 => w_acc2,
            i_acc3 => w_acc3,
            i_acc4 => w_acc4,
            i_sel  => w_z,
            o_out  => w_acc_out_kz_calc);
            
  -- multiplexador dos contadores
  u_muxs_count : mux_count_for_kzcalc 
  port map (i_count0 => w_count0,
            i_count1 => w_count1,
            i_count2 => w_count2,
            i_count3 => w_count3,
            i_count4 => w_count4,
            i_sel    => w_z,
            o_out    => w_count_out_kz_calc);
  
  -- calculo de kz e uz (valor de acumulador e contador vem de um mux com base na banda atual)
  u_kz_uz_calc : kz_calc 
  port map ( i_clk       => i_clk,
             i_en        => i_en_calc_kz_uz,
             i_acc_reg   => w_acc_out_kz_calc,
             i_count_reg => w_count_out_kz_calc,
             i_mapped    => w_mapped,
             o_kz        => w_kz,
             o_uz        => w_uz);         
  
  o_uz <= w_uz;    
  
   
  -- encode por uzkz
  u_encode_uzkz : encode_uzkz 
  port map (i_clk           => i_clk,
            i_en            => i_en_encode_uzkz,
            i_kz            => w_kz,
            i_uz            => w_uz,
            i_mapped        => w_mapped,
            o_encode        => w_encoded_uzkz,
            o_bits_written  => w_bits_written_encoded_uzkz);     
  
  u_encode_umax : encode_umax
  port map (i_clk          => i_clk,
            i_en           => i_en_encode_umax,
            i_mapped       => w_mapped,
            o_encode       => w_encoded_umax,
            o_bits_written => w_bits_written_encoded_umax);
  
  u_encode_dmapped : encode_d_mapped 
  port map(i_clk          => i_clk,
           i_en           => i_en_encode_mapped,
           i_mapped       => w_mapped,
           o_encode       => w_encoded_dmapped,
           o_bits_written => w_bits_written_encoded_dmapped);
  
  u_mux_encoded_output : mux_select_output_encodeds
  port map(i_uzkz_encoded    => w_encoded_uzkz,
           i_umax_encoded    => w_encoded_umax,
           i_dmapped_encoded => w_encoded_dmapped,
           i_sel             => i_sel_muxs_encoded,
           o_encoded_out     => w_out_encoded);
  
  o_out_encoded <= w_out_encoded;
  
  u_mux_bitswritten : mux_bits_written 
  port map (i_bits_uzkz    => w_bits_written_encoded_uzkz,    
            i_bits_umax    => w_bits_written_encoded_umax,  
            i_bits_dmapped => w_bits_written_encoded_dmapped,
            i_sel          => i_sel_muxs_encoded,
            o_bits_written => w_out_bitswritten);
  
  o_out_bits_written <= w_out_bitswritten;

end Behavioral;
