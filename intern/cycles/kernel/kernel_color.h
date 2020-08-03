/*
 * Copyright 2011-2018 Blender Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __KERNEL_COLOR_H__
#define __KERNEL_COLOR_H__

#include "util/util_color.h"

CCL_NAMESPACE_BEGIN

/* Wavelength to XYZ LUT. Range 360 - 830, step 1. */
ccl_static_constant float wavelength_xyz_lookup[][3] = {
    {0.000129900000f, 0.000003917000f, 0.000606100000f},
    {0.000145847000f, 0.000004393581f, 0.000680879200f},
    {0.000163802100f, 0.000004929604f, 0.000765145600f},
    {0.000184003700f, 0.000005532136f, 0.000860012400f},
    {0.000206690200f, 0.000006208245f, 0.000966592800f},
    {0.000232100000f, 0.000006965000f, 0.001086000000f},
    {0.000260728000f, 0.000007813219f, 0.001220586000f},
    {0.000293075000f, 0.000008767336f, 0.001372729000f},
    {0.000329388000f, 0.000009839844f, 0.001543579000f},
    {0.000369914000f, 0.000011043230f, 0.001734286000f},
    {0.000414900000f, 0.000012390000f, 0.001946000000f},
    {0.000464158700f, 0.000013886410f, 0.002177777000f},
    {0.000518986000f, 0.000015557280f, 0.002435809000f},
    {0.000581854000f, 0.000017442960f, 0.002731953000f},
    {0.000655234700f, 0.000019583750f, 0.003078064000f},
    {0.000741600000f, 0.000022020000f, 0.003486000000f},
    {0.000845029600f, 0.000024839650f, 0.003975227000f},
    {0.000964526800f, 0.000028041260f, 0.004540880000f},
    {0.001094949000f, 0.000031531040f, 0.005158320000f},
    {0.001231154000f, 0.000035215210f, 0.005802907000f},
    {0.001368000000f, 0.000039000000f, 0.006450001000f},
    {0.001502050000f, 0.000042826400f, 0.007083216000f},
    {0.001642328000f, 0.000046914600f, 0.007745488000f},
    {0.001802382000f, 0.000051589600f, 0.008501152000f},
    {0.001995757000f, 0.000057176400f, 0.009414544000f},
    {0.002236000000f, 0.000064000000f, 0.010549990000f},
    {0.002535385000f, 0.000072344210f, 0.011965800000f},
    {0.002892603000f, 0.000082212240f, 0.013655870000f},
    {0.003300829000f, 0.000093508160f, 0.015588050000f},
    {0.003753236000f, 0.000106136100f, 0.017730150000f},
    {0.004243000000f, 0.000120000000f, 0.020050010000f},
    {0.004762389000f, 0.000134984000f, 0.022511360000f},
    {0.005330048000f, 0.000151492000f, 0.025202880000f},
    {0.005978712000f, 0.000170208000f, 0.028279720000f},
    {0.006741117000f, 0.000191816000f, 0.031897040000f},
    {0.007650000000f, 0.000217000000f, 0.036210000000f},
    {0.008751373000f, 0.000246906700f, 0.041437710000f},
    {0.010028880000f, 0.000281240000f, 0.047503720000f},
    {0.011421700000f, 0.000318520000f, 0.054119880000f},
    {0.012869010000f, 0.000357266700f, 0.060998030000f},
    {0.014310000000f, 0.000396000000f, 0.067850010000f},
    {0.015704430000f, 0.000433714700f, 0.074486320000f},
    {0.017147440000f, 0.000473024000f, 0.081361560000f},
    {0.018781220000f, 0.000517876000f, 0.089153640000f},
    {0.020748010000f, 0.000572218700f, 0.098540480000f},
    {0.023190000000f, 0.000640000000f, 0.110200000000f},
    {0.026207360000f, 0.000724560000f, 0.124613300000f},
    {0.029782480000f, 0.000825500000f, 0.141701700000f},
    {0.033880920000f, 0.000941160000f, 0.161303500000f},
    {0.038468240000f, 0.001069880000f, 0.183256800000f},
    {0.043510000000f, 0.001210000000f, 0.207400000000f},
    {0.048995600000f, 0.001362091000f, 0.233692100000f},
    {0.055022600000f, 0.001530752000f, 0.262611400000f},
    {0.061718800000f, 0.001720368000f, 0.294774600000f},
    {0.069212000000f, 0.001935323000f, 0.330798500000f},
    {0.077630000000f, 0.002180000000f, 0.371300000000f},
    {0.086958110000f, 0.002454800000f, 0.416209100000f},
    {0.097176720000f, 0.002764000000f, 0.465464200000f},
    {0.108406300000f, 0.003117800000f, 0.519694800000f},
    {0.120767200000f, 0.003526400000f, 0.579530300000f},
    {0.134380000000f, 0.004000000000f, 0.645600000000f},
    {0.149358200000f, 0.004546240000f, 0.718483800000f},
    {0.165395700000f, 0.005159320000f, 0.796713300000f},
    {0.181983100000f, 0.005829280000f, 0.877845900000f},
    {0.198611000000f, 0.006546160000f, 0.959439000000f},
    {0.214770000000f, 0.007300000000f, 1.039050100000f},
    {0.230186800000f, 0.008086507000f, 1.115367300000f},
    {0.244879700000f, 0.008908720000f, 1.188497100000f},
    {0.258777300000f, 0.009767680000f, 1.258123300000f},
    {0.271807900000f, 0.010664430000f, 1.323929600000f},
    {0.283900000000f, 0.011600000000f, 1.385600000000f},
    {0.294943800000f, 0.012573170000f, 1.442635200000f},
    {0.304896500000f, 0.013582720000f, 1.494803500000f},
    {0.313787300000f, 0.014629680000f, 1.542190300000f},
    {0.321645400000f, 0.015715090000f, 1.584880700000f},
    {0.328500000000f, 0.016840000000f, 1.622960000000f},
    {0.334351300000f, 0.018007360000f, 1.656404800000f},
    {0.339210100000f, 0.019214480000f, 1.685295900000f},
    {0.343121300000f, 0.020453920000f, 1.709874500000f},
    {0.346129600000f, 0.021718240000f, 1.730382100000f},
    {0.348280000000f, 0.023000000000f, 1.747060000000f},
    {0.349599900000f, 0.024294610000f, 1.760044600000f},
    {0.350147400000f, 0.025610240000f, 1.769623300000f},
    {0.350013000000f, 0.026958570000f, 1.776263700000f},
    {0.349287000000f, 0.028351250000f, 1.780433400000f},
    {0.348060000000f, 0.029800000000f, 1.782600000000f},
    {0.346373300000f, 0.031310830000f, 1.782968200000f},
    {0.344262400000f, 0.032883680000f, 1.781699800000f},
    {0.341808800000f, 0.034521120000f, 1.779198200000f},
    {0.339094100000f, 0.036225710000f, 1.775867100000f},
    {0.336200000000f, 0.038000000000f, 1.772110000000f},
    {0.333197700000f, 0.039846670000f, 1.768258900000f},
    {0.330041100000f, 0.041768000000f, 1.764039000000f},
    {0.326635700000f, 0.043766000000f, 1.758943800000f},
    {0.322886800000f, 0.045842670000f, 1.752466300000f},
    {0.318700000000f, 0.048000000000f, 1.744100000000f},
    {0.314025100000f, 0.050243680000f, 1.733559500000f},
    {0.308884000000f, 0.052573040000f, 1.720858100000f},
    {0.303290400000f, 0.054980560000f, 1.705936900000f},
    {0.297257900000f, 0.057458720000f, 1.688737200000f},
    {0.290800000000f, 0.060000000000f, 1.669200000000f},
    {0.283970100000f, 0.062601970000f, 1.647528700000f},
    {0.276721400000f, 0.065277520000f, 1.623412700000f},
    {0.268917800000f, 0.068042080000f, 1.596022300000f},
    {0.260422700000f, 0.070911090000f, 1.564528000000f},
    {0.251100000000f, 0.073900000000f, 1.528100000000f},
    {0.240847500000f, 0.077016000000f, 1.486111400000f},
    {0.229851200000f, 0.080266400000f, 1.439521500000f},
    {0.218407200000f, 0.083666800000f, 1.389879900000f},
    {0.206811500000f, 0.087232800000f, 1.338736200000f},
    {0.195360000000f, 0.090980000000f, 1.287640000000f},
    {0.184213600000f, 0.094917550000f, 1.237422300000f},
    {0.173327300000f, 0.099045840000f, 1.187824300000f},
    {0.162688100000f, 0.103367400000f, 1.138761100000f},
    {0.152283300000f, 0.107884600000f, 1.090148000000f},
    {0.142100000000f, 0.112600000000f, 1.041900000000f},
    {0.132178600000f, 0.117532000000f, 0.994197600000f},
    {0.122569600000f, 0.122674400000f, 0.947347300000f},
    {0.113275200000f, 0.127992800000f, 0.901453100000f},
    {0.104297900000f, 0.133452800000f, 0.856619300000f},
    {0.095640000000f, 0.139020000000f, 0.812950100000f},
    {0.087299550000f, 0.144676400000f, 0.770517300000f},
    {0.079308040000f, 0.150469300000f, 0.729444800000f},
    {0.071717760000f, 0.156461900000f, 0.689913600000f},
    {0.064580990000f, 0.162717700000f, 0.652104900000f},
    {0.057950010000f, 0.169300000000f, 0.616200000000f},
    {0.051862110000f, 0.176243100000f, 0.582328600000f},
    {0.046281520000f, 0.183558100000f, 0.550416200000f},
    {0.041150880000f, 0.191273500000f, 0.520337600000f},
    {0.036412830000f, 0.199418000000f, 0.491967300000f},
    {0.032010000000f, 0.208020000000f, 0.465180000000f},
    {0.027917200000f, 0.217119900000f, 0.439924600000f},
    {0.024144400000f, 0.226734500000f, 0.416183600000f},
    {0.020687000000f, 0.236857100000f, 0.393882200000f},
    {0.017540400000f, 0.247481200000f, 0.372945900000f},
    {0.014700000000f, 0.258600000000f, 0.353300000000f},
    {0.012161790000f, 0.270184900000f, 0.334857800000f},
    {0.009919960000f, 0.282293900000f, 0.317552100000f},
    {0.007967240000f, 0.295050500000f, 0.301337500000f},
    {0.006296346000f, 0.308578000000f, 0.286168600000f},
    {0.004900000000f, 0.323000000000f, 0.272000000000f},
    {0.003777173000f, 0.338402100000f, 0.258817100000f},
    {0.002945320000f, 0.354685800000f, 0.246483800000f},
    {0.002424880000f, 0.371698600000f, 0.234771800000f},
    {0.002236293000f, 0.389287500000f, 0.223453300000f},
    {0.002400000000f, 0.407300000000f, 0.212300000000f},
    {0.002925520000f, 0.425629900000f, 0.201169200000f},
    {0.003836560000f, 0.444309600000f, 0.190119600000f},
    {0.005174840000f, 0.463394400000f, 0.179225400000f},
    {0.006982080000f, 0.482939500000f, 0.168560800000f},
    {0.009300000000f, 0.503000000000f, 0.158200000000f},
    {0.012149490000f, 0.523569300000f, 0.148138300000f},
    {0.015535880000f, 0.544512000000f, 0.138375800000f},
    {0.019477520000f, 0.565690000000f, 0.128994200000f},
    {0.023992770000f, 0.586965300000f, 0.120075100000f},
    {0.029100000000f, 0.608200000000f, 0.111700000000f},
    {0.034814850000f, 0.629345600000f, 0.103904800000f},
    {0.041120160000f, 0.650306800000f, 0.096667480000f},
    {0.047985040000f, 0.670875200000f, 0.089982720000f},
    {0.055378610000f, 0.690842400000f, 0.083845310000f},
    {0.063270000000f, 0.710000000000f, 0.078249990000f},
    {0.071635010000f, 0.728185200000f, 0.073208990000f},
    {0.080462240000f, 0.745463600000f, 0.068678160000f},
    {0.089739960000f, 0.761969400000f, 0.064567840000f},
    {0.099456450000f, 0.777836800000f, 0.060788350000f},
    {0.109600000000f, 0.793200000000f, 0.057250010000f},
    {0.120167400000f, 0.808110400000f, 0.053904350000f},
    {0.131114500000f, 0.822496200000f, 0.050746640000f},
    {0.142367900000f, 0.836306800000f, 0.047752760000f},
    {0.153854200000f, 0.849491600000f, 0.044898590000f},
    {0.165500000000f, 0.862000000000f, 0.042160000000f},
    {0.177257100000f, 0.873810800000f, 0.039507280000f},
    {0.189140000000f, 0.884962400000f, 0.036935640000f},
    {0.201169400000f, 0.895493600000f, 0.034458360000f},
    {0.213365800000f, 0.905443200000f, 0.032088720000f},
    {0.225749900000f, 0.914850100000f, 0.029840000000f},
    {0.238320900000f, 0.923734800000f, 0.027711810000f},
    {0.251066800000f, 0.932092400000f, 0.025694440000f},
    {0.263992200000f, 0.939922600000f, 0.023787160000f},
    {0.277101700000f, 0.947225200000f, 0.021989250000f},
    {0.290400000000f, 0.954000000000f, 0.020300000000f},
    {0.303891200000f, 0.960256100000f, 0.018718050000f},
    {0.317572600000f, 0.966007400000f, 0.017240360000f},
    {0.331438400000f, 0.971260600000f, 0.015863640000f},
    {0.345482800000f, 0.976022500000f, 0.014584610000f},
    {0.359700000000f, 0.980300000000f, 0.013400000000f},
    {0.374083900000f, 0.984092400000f, 0.012307230000f},
    {0.388639600000f, 0.987418200000f, 0.011301880000f},
    {0.403378400000f, 0.990312800000f, 0.010377920000f},
    {0.418311500000f, 0.992811600000f, 0.009529306000f},
    {0.433449900000f, 0.994950100000f, 0.008749999000f},
    {0.448795300000f, 0.996710800000f, 0.008035200000f},
    {0.464336000000f, 0.998098300000f, 0.007381600000f},
    {0.480064000000f, 0.999112000000f, 0.006785400000f},
    {0.495971300000f, 0.999748200000f, 0.006242800000f},
    {0.512050100000f, 1.000000000000f, 0.005749999000f},
    {0.528295900000f, 0.999856700000f, 0.005303600000f},
    {0.544691600000f, 0.999304600000f, 0.004899800000f},
    {0.561209400000f, 0.998325500000f, 0.004534200000f},
    {0.577821500000f, 0.996898700000f, 0.004202400000f},
    {0.594500000000f, 0.995000000000f, 0.003900000000f},
    {0.611220900000f, 0.992600500000f, 0.003623200000f},
    {0.627975800000f, 0.989742600000f, 0.003370600000f},
    {0.644760200000f, 0.986444400000f, 0.003141400000f},
    {0.661569700000f, 0.982724100000f, 0.002934800000f},
    {0.678400000000f, 0.978600000000f, 0.002749999000f},
    {0.695239200000f, 0.974083700000f, 0.002585200000f},
    {0.712058600000f, 0.969171200000f, 0.002438600000f},
    {0.728828400000f, 0.963856800000f, 0.002309400000f},
    {0.745518800000f, 0.958134900000f, 0.002196800000f},
    {0.762100000000f, 0.952000000000f, 0.002100000000f},
    {0.778543200000f, 0.945450400000f, 0.002017733000f},
    {0.794825600000f, 0.938499200000f, 0.001948200000f},
    {0.810926400000f, 0.931162800000f, 0.001889800000f},
    {0.826824800000f, 0.923457600000f, 0.001840933000f},
    {0.842500000000f, 0.915400000000f, 0.001800000000f},
    {0.857932500000f, 0.907006400000f, 0.001766267000f},
    {0.873081600000f, 0.898277200000f, 0.001737800000f},
    {0.887894400000f, 0.889204800000f, 0.001711200000f},
    {0.902318100000f, 0.879781600000f, 0.001683067000f},
    {0.916300000000f, 0.870000000000f, 0.001650001000f},
    {0.929799500000f, 0.859861300000f, 0.001610133000f},
    {0.942798400000f, 0.849392000000f, 0.001564400000f},
    {0.955277600000f, 0.838622000000f, 0.001513600000f},
    {0.967217900000f, 0.827581300000f, 0.001458533000f},
    {0.978600000000f, 0.816300000000f, 0.001400000000f},
    {0.989385600000f, 0.804794700000f, 0.001336667000f},
    {0.999548800000f, 0.793082000000f, 0.001270000000f},
    {1.009089200000f, 0.781192000000f, 0.001205000000f},
    {1.018006400000f, 0.769154700000f, 0.001146667000f},
    {1.026300000000f, 0.757000000000f, 0.001100000000f},
    {1.033982700000f, 0.744754100000f, 0.001068800000f},
    {1.040986000000f, 0.732422400000f, 0.001049400000f},
    {1.047188000000f, 0.720003600000f, 0.001035600000f},
    {1.052466700000f, 0.707496500000f, 0.001021200000f},
    {1.056700000000f, 0.694900000000f, 0.001000000000f},
    {1.059794400000f, 0.682219200000f, 0.000968640000f},
    {1.061799200000f, 0.669471600000f, 0.000929920000f},
    {1.062806800000f, 0.656674400000f, 0.000886880000f},
    {1.062909600000f, 0.643844800000f, 0.000842560000f},
    {1.062200000000f, 0.631000000000f, 0.000800000000f},
    {1.060735200000f, 0.618155500000f, 0.000760960000f},
    {1.058443600000f, 0.605314400000f, 0.000723680000f},
    {1.055224400000f, 0.592475600000f, 0.000685920000f},
    {1.050976800000f, 0.579637900000f, 0.000645440000f},
    {1.045600000000f, 0.566800000000f, 0.000600000000f},
    {1.039036900000f, 0.553961100000f, 0.000547866700f},
    {1.031360800000f, 0.541137200000f, 0.000491600000f},
    {1.022666200000f, 0.528352800000f, 0.000435400000f},
    {1.013047700000f, 0.515632300000f, 0.000383466700f},
    {1.002600000000f, 0.503000000000f, 0.000340000000f},
    {0.991367500000f, 0.490468800000f, 0.000307253300f},
    {0.979331400000f, 0.478030400000f, 0.000283160000f},
    {0.966491600000f, 0.465677600000f, 0.000265440000f},
    {0.952847900000f, 0.453403200000f, 0.000251813300f},
    {0.938400000000f, 0.441200000000f, 0.000240000000f},
    {0.923194000000f, 0.429080000000f, 0.000229546700f},
    {0.907244000000f, 0.417036000000f, 0.000220640000f},
    {0.890502000000f, 0.405032000000f, 0.000211960000f},
    {0.872920000000f, 0.393032000000f, 0.000202186700f},
    {0.854449900000f, 0.381000000000f, 0.000190000000f},
    {0.835084000000f, 0.368918400000f, 0.000174213300f},
    {0.814946000000f, 0.356827200000f, 0.000155640000f},
    {0.794186000000f, 0.344776800000f, 0.000135960000f},
    {0.772954000000f, 0.332817600000f, 0.000116853300f},
    {0.751400000000f, 0.321000000000f, 0.000100000000f},
    {0.729583600000f, 0.309338100000f, 0.000086133330f},
    {0.707588800000f, 0.297850400000f, 0.000074600000f},
    {0.685602200000f, 0.286593600000f, 0.000065000000f},
    {0.663810400000f, 0.275624500000f, 0.000056933330f},
    {0.642400000000f, 0.265000000000f, 0.000049999990f},
    {0.621514900000f, 0.254763200000f, 0.000044160000f},
    {0.601113800000f, 0.244889600000f, 0.000039480000f},
    {0.581105200000f, 0.235334400000f, 0.000035720000f},
    {0.561397700000f, 0.226052800000f, 0.000032640000f},
    {0.541900000000f, 0.217000000000f, 0.000030000000f},
    {0.522599500000f, 0.208161600000f, 0.000027653330f},
    {0.503546400000f, 0.199548800000f, 0.000025560000f},
    {0.484743600000f, 0.191155200000f, 0.000023640000f},
    {0.466193900000f, 0.182974400000f, 0.000021813330f},
    {0.447900000000f, 0.175000000000f, 0.000020000000f},
    {0.429861300000f, 0.167223500000f, 0.000018133330f},
    {0.412098000000f, 0.159646400000f, 0.000016200000f},
    {0.394644000000f, 0.152277600000f, 0.000014200000f},
    {0.377533300000f, 0.145125900000f, 0.000012133330f},
    {0.360800000000f, 0.138200000000f, 0.000010000000f},
    {0.344456300000f, 0.131500300000f, 0.000007733333f},
    {0.328516800000f, 0.125024800000f, 0.000005400000f},
    {0.313019200000f, 0.118779200000f, 0.000003200000f},
    {0.298001100000f, 0.112769100000f, 0.000001333333f},
    {0.283500000000f, 0.107000000000f, 0.000000000000f},
    {0.269544800000f, 0.101476200000f, 0.000000000000f},
    {0.256118400000f, 0.096188640000f, 0.000000000000f},
    {0.243189600000f, 0.091122960000f, 0.000000000000f},
    {0.230727200000f, 0.086264850000f, 0.000000000000f},
    {0.218700000000f, 0.081600000000f, 0.000000000000f},
    {0.207097100000f, 0.077120640000f, 0.000000000000f},
    {0.195923200000f, 0.072825520000f, 0.000000000000f},
    {0.185170800000f, 0.068710080000f, 0.000000000000f},
    {0.174832300000f, 0.064769760000f, 0.000000000000f},
    {0.164900000000f, 0.061000000000f, 0.000000000000f},
    {0.155366700000f, 0.057396210000f, 0.000000000000f},
    {0.146230000000f, 0.053955040000f, 0.000000000000f},
    {0.137490000000f, 0.050673760000f, 0.000000000000f},
    {0.129146700000f, 0.047549650000f, 0.000000000000f},
    {0.121200000000f, 0.044580000000f, 0.000000000000f},
    {0.113639700000f, 0.041758720000f, 0.000000000000f},
    {0.106465000000f, 0.039084960000f, 0.000000000000f},
    {0.099690440000f, 0.036563840000f, 0.000000000000f},
    {0.093330610000f, 0.034200480000f, 0.000000000000f},
    {0.087400000000f, 0.032000000000f, 0.000000000000f},
    {0.081900960000f, 0.029962610000f, 0.000000000000f},
    {0.076804280000f, 0.028076640000f, 0.000000000000f},
    {0.072077120000f, 0.026329360000f, 0.000000000000f},
    {0.067686640000f, 0.024708050000f, 0.000000000000f},
    {0.063600000000f, 0.023200000000f, 0.000000000000f},
    {0.059806850000f, 0.021800770000f, 0.000000000000f},
    {0.056282160000f, 0.020501120000f, 0.000000000000f},
    {0.052971040000f, 0.019281080000f, 0.000000000000f},
    {0.049818610000f, 0.018120690000f, 0.000000000000f},
    {0.046770000000f, 0.017000000000f, 0.000000000000f},
    {0.043784050000f, 0.015903790000f, 0.000000000000f},
    {0.040875360000f, 0.014837180000f, 0.000000000000f},
    {0.038072640000f, 0.013810680000f, 0.000000000000f},
    {0.035404610000f, 0.012834780000f, 0.000000000000f},
    {0.032900000000f, 0.011920000000f, 0.000000000000f},
    {0.030564190000f, 0.011068310000f, 0.000000000000f},
    {0.028380560000f, 0.010273390000f, 0.000000000000f},
    {0.026344840000f, 0.009533311000f, 0.000000000000f},
    {0.024452750000f, 0.008846157000f, 0.000000000000f},
    {0.022700000000f, 0.008210000000f, 0.000000000000f},
    {0.021084290000f, 0.007623781000f, 0.000000000000f},
    {0.019599880000f, 0.007085424000f, 0.000000000000f},
    {0.018237320000f, 0.006591476000f, 0.000000000000f},
    {0.016987170000f, 0.006138485000f, 0.000000000000f},
    {0.015840000000f, 0.005723000000f, 0.000000000000f},
    {0.014790640000f, 0.005343059000f, 0.000000000000f},
    {0.013831320000f, 0.004995796000f, 0.000000000000f},
    {0.012948680000f, 0.004676404000f, 0.000000000000f},
    {0.012129200000f, 0.004380075000f, 0.000000000000f},
    {0.011359160000f, 0.004102000000f, 0.000000000000f},
    {0.010629350000f, 0.003838453000f, 0.000000000000f},
    {0.009938846000f, 0.003589099000f, 0.000000000000f},
    {0.009288422000f, 0.003354219000f, 0.000000000000f},
    {0.008678854000f, 0.003134093000f, 0.000000000000f},
    {0.008110916000f, 0.002929000000f, 0.000000000000f},
    {0.007582388000f, 0.002738139000f, 0.000000000000f},
    {0.007088746000f, 0.002559876000f, 0.000000000000f},
    {0.006627313000f, 0.002393244000f, 0.000000000000f},
    {0.006195408000f, 0.002237275000f, 0.000000000000f},
    {0.005790346000f, 0.002091000000f, 0.000000000000f},
    {0.005409826000f, 0.001953587000f, 0.000000000000f},
    {0.005052583000f, 0.001824580000f, 0.000000000000f},
    {0.004717512000f, 0.001703580000f, 0.000000000000f},
    {0.004403507000f, 0.001590187000f, 0.000000000000f},
    {0.004109457000f, 0.001484000000f, 0.000000000000f},
    {0.003833913000f, 0.001384496000f, 0.000000000000f},
    {0.003575748000f, 0.001291268000f, 0.000000000000f},
    {0.003334342000f, 0.001204092000f, 0.000000000000f},
    {0.003109075000f, 0.001122744000f, 0.000000000000f},
    {0.002899327000f, 0.001047000000f, 0.000000000000f},
    {0.002704348000f, 0.000976589600f, 0.000000000000f},
    {0.002523020000f, 0.000911108800f, 0.000000000000f},
    {0.002354168000f, 0.000850133200f, 0.000000000000f},
    {0.002196616000f, 0.000793238400f, 0.000000000000f},
    {0.002049190000f, 0.000740000000f, 0.000000000000f},
    {0.001910960000f, 0.000690082700f, 0.000000000000f},
    {0.001781438000f, 0.000643310000f, 0.000000000000f},
    {0.001660110000f, 0.000599496000f, 0.000000000000f},
    {0.001546459000f, 0.000558454700f, 0.000000000000f},
    {0.001439971000f, 0.000520000000f, 0.000000000000f},
    {0.001340042000f, 0.000483913600f, 0.000000000000f},
    {0.001246275000f, 0.000450052800f, 0.000000000000f},
    {0.001158471000f, 0.000418345200f, 0.000000000000f},
    {0.001076430000f, 0.000388718400f, 0.000000000000f},
    {0.000999949300f, 0.000361100000f, 0.000000000000f},
    {0.000928735800f, 0.000335383500f, 0.000000000000f},
    {0.000862433200f, 0.000311440400f, 0.000000000000f},
    {0.000800750300f, 0.000289165600f, 0.000000000000f},
    {0.000743396000f, 0.000268453900f, 0.000000000000f},
    {0.000690078600f, 0.000249200000f, 0.000000000000f},
    {0.000640515600f, 0.000231301900f, 0.000000000000f},
    {0.000594502100f, 0.000214685600f, 0.000000000000f},
    {0.000551864600f, 0.000199288400f, 0.000000000000f},
    {0.000512429000f, 0.000185047500f, 0.000000000000f},
    {0.000476021300f, 0.000171900000f, 0.000000000000f},
    {0.000442453600f, 0.000159778100f, 0.000000000000f},
    {0.000411511700f, 0.000148604400f, 0.000000000000f},
    {0.000382981400f, 0.000138301600f, 0.000000000000f},
    {0.000356649100f, 0.000128792500f, 0.000000000000f},
    {0.000332301100f, 0.000120000000f, 0.000000000000f},
    {0.000309758600f, 0.000111859500f, 0.000000000000f},
    {0.000288887100f, 0.000104322400f, 0.000000000000f},
    {0.000269539400f, 0.000097335600f, 0.000000000000f},
    {0.000251568200f, 0.000090845870f, 0.000000000000f},
    {0.000234826100f, 0.000084800000f, 0.000000000000f},
    {0.000219171000f, 0.000079146670f, 0.000000000000f},
    {0.000204525800f, 0.000073858000f, 0.000000000000f},
    {0.000190840500f, 0.000068916000f, 0.000000000000f},
    {0.000178065400f, 0.000064302670f, 0.000000000000f},
    {0.000166150500f, 0.000060000000f, 0.000000000000f},
    {0.000155023600f, 0.000055981870f, 0.000000000000f},
    {0.000144621900f, 0.000052225600f, 0.000000000000f},
    {0.000134909800f, 0.000048718400f, 0.000000000000f},
    {0.000125852000f, 0.000045447470f, 0.000000000000f},
    {0.000117413000f, 0.000042400000f, 0.000000000000f},
    {0.000109551500f, 0.000039561040f, 0.000000000000f},
    {0.000102224500f, 0.000036915120f, 0.000000000000f},
    {0.000095394450f, 0.000034448680f, 0.000000000000f},
    {0.000089023900f, 0.000032148160f, 0.000000000000f},
    {0.000083075270f, 0.000030000000f, 0.000000000000f},
    {0.000077512690f, 0.000027991250f, 0.000000000000f},
    {0.000072313040f, 0.000026113560f, 0.000000000000f},
    {0.000067457780f, 0.000024360240f, 0.000000000000f},
    {0.000062928440f, 0.000022724610f, 0.000000000000f},
    {0.000058706520f, 0.000021200000f, 0.000000000000f},
    {0.000054770280f, 0.000019778550f, 0.000000000000f},
    {0.000051099180f, 0.000018452850f, 0.000000000000f},
    {0.000047676540f, 0.000017216870f, 0.000000000000f},
    {0.000044485670f, 0.000016064590f, 0.000000000000f},
    {0.000041509940f, 0.000014990000f, 0.000000000000f},
    {0.000038733240f, 0.000013987280f, 0.000000000000f},
    {0.000036142030f, 0.000013051550f, 0.000000000000f},
    {0.000033723520f, 0.000012178180f, 0.000000000000f},
    {0.000031464870f, 0.000011362540f, 0.000000000000f},
    {0.000029353260f, 0.000010600000f, 0.000000000000f},
    {0.000027375730f, 0.000009885877f, 0.000000000000f},
    {0.000025524330f, 0.000009217304f, 0.000000000000f},
    {0.000023793760f, 0.000008592362f, 0.000000000000f},
    {0.000022178700f, 0.000008009133f, 0.000000000000f},
    {0.000020673830f, 0.000007465700f, 0.000000000000f},
    {0.000019272260f, 0.000006959567f, 0.000000000000f},
    {0.000017966400f, 0.000006487995f, 0.000000000000f},
    {0.000016749910f, 0.000006048699f, 0.000000000000f},
    {0.000015616480f, 0.000005639396f, 0.000000000000f},
    {0.000014559770f, 0.000005257800f, 0.000000000000f},
    {0.000013573870f, 0.000004901771f, 0.000000000000f},
    {0.000012654360f, 0.000004569720f, 0.000000000000f},
    {0.000011797230f, 0.000004260194f, 0.000000000000f},
    {0.000010998440f, 0.000003971739f, 0.000000000000f},
    {0.000010253980f, 0.000003702900f, 0.000000000000f},
    {0.000009559646f, 0.000003452163f, 0.000000000000f},
    {0.000008912044f, 0.000003218302f, 0.000000000000f},
    {0.000008308358f, 0.000003000300f, 0.000000000000f},
    {0.000007745769f, 0.000002797139f, 0.000000000000f},
    {0.000007221456f, 0.000002607800f, 0.000000000000f},
    {0.000006732475f, 0.000002431220f, 0.000000000000f},
    {0.000006276423f, 0.000002266531f, 0.000000000000f},
    {0.000005851304f, 0.000002113013f, 0.000000000000f},
    {0.000005455118f, 0.000001969943f, 0.000000000000f},
    {0.000005085868f, 0.000001836600f, 0.000000000000f},
    {0.000004741466f, 0.000001712230f, 0.000000000000f},
    {0.000004420236f, 0.000001596228f, 0.000000000000f},
    {0.000004120783f, 0.000001488090f, 0.000000000000f},
    {0.000003841716f, 0.000001387314f, 0.000000000000f},
    {0.000003581652f, 0.000001293400f, 0.000000000000f},
    {0.000003339127f, 0.000001205820f, 0.000000000000f},
    {0.000003112949f, 0.000001124143f, 0.000000000000f},
    {0.000002902121f, 0.000001048009f, 0.000000000000f},
    {0.000002705645f, 0.000000977058f, 0.000000000000f},
    {0.000002522525f, 0.000000910930f, 0.000000000000f},
    {0.000002351726f, 0.000000849251f, 0.000000000000f},
    {0.000002192415f, 0.000000791721f, 0.000000000000f},
    {0.000002043902f, 0.000000738090f, 0.000000000000f},
    {0.000001905497f, 0.000000688110f, 0.000000000000f},
    {0.000001776509f, 0.000000641530f, 0.000000000000f},
    {0.000001656215f, 0.000000598090f, 0.000000000000f},
    {0.000001544022f, 0.000000557575f, 0.000000000000f},
    {0.000001439440f, 0.000000519808f, 0.000000000000f},
    {0.000001341977f, 0.000000484612f, 0.000000000000f},
    {0.000001251141f, 0.000000451810f, 0.000000000000f}};

/* Rec709 RGB to wavelength intensities LUT. Range 360 - 830, step 5. */
ccl_static_constant float rec709_wavelength_lookup[][3] = {
    {0.000902743f, 0.000440162f, 0.998533177f}, {0.000904961f, 0.000380023f, 0.998616619f},
    {0.000910956f, 0.000333280f, 0.998679237f}, {0.000929552f, 0.000288705f, 0.998722748f},
    {0.000948679f, 0.000177288f, 0.998800211f}, {0.001035677f, 0.000081514f, 0.998789905f},
    {0.001172521f, 0.000017206f, 0.998713427f}, {0.001310703f, 0.000001561f, 0.998637909f},
    {0.001458567f, 0.000000654f, 0.998455594f}, {0.001733331f, 0.000000085f, 0.998164365f},
    {0.002095915f, 0.000000000f, 0.997896646f}, {0.002577116f, 0.000000000f, 0.997321487f},
    {0.003201633f, 0.000000000f, 0.996730175f}, {0.004265045f, 0.000000000f, 0.995700589f},
    {0.005920357f, 0.000000000f, 0.994063584f}, {0.008506606f, 0.000000000f, 0.991482264f},
    {0.012443321f, 0.000000000f, 0.987517388f}, {0.018091684f, 0.000000000f, 0.981856793f},
    {0.026042546f, 0.000000000f, 0.973856578f}, {0.036435460f, 0.000000000f, 0.962707910f},
    {0.039899931f, 0.021478954f, 0.937650135f}, {0.035286134f, 0.067640816f, 0.896123859f},
    {0.025361256f, 0.134467863f, 0.839298811f}, {0.013658174f, 0.216312735f, 0.769219525f},
    {0.003834335f, 0.307345736f, 0.688087554f}, {0.000000000f, 0.401523232f, 0.598004484f},
    {0.000000000f, 0.496354267f, 0.503380479f}, {0.000000000f, 0.590572707f, 0.409329548f},
    {0.000000000f, 0.681367728f, 0.318629075f}, {0.000000000f, 0.766235410f, 0.233873901f},
    {0.000000000f, 0.842162175f, 0.158131443f}, {0.000000000f, 0.906067124f, 0.094291632f},
    {0.000000000f, 0.955194216f, 0.045290110f}, {0.000000000f, 0.986988908f, 0.013492779f},
    {0.000000000f, 1.000000000f, 0.000219097f}, {0.000000000f, 1.000000000f, 0.000000000f},
    {0.000000000f, 1.000000000f, 0.000000000f}, {0.000000000f, 1.000000000f, 0.000000000f},
    {0.000000000f, 1.000000000f, 0.000000000f}, {0.000000000f, 1.000000000f, 0.000000000f},
    {0.000000000f, 0.999067127f, 0.001246220f}, {0.005379110f, 0.980188726f, 0.013856898f},
    {0.044486502f, 0.932391013f, 0.022648652f}, {0.111111509f, 0.860799874f, 0.027696770f},
    {0.198844202f, 0.771137366f, 0.029718483f}, {0.300756170f, 0.669781804f, 0.029315467f},
    {0.410294383f, 0.562642966f, 0.027020612f}, {0.520986174f, 0.455607353f, 0.023492681f},
    {0.627185352f, 0.353591880f, 0.019379970f}, {0.724277585f, 0.260824478f, 0.015114317f},
    {0.808674320f, 0.180647965f, 0.010966287f}, {0.878054831f, 0.114912917f, 0.007294643f},
    {0.931326097f, 0.064454707f, 0.004495005f}, {0.968697501f, 0.029231565f, 0.002312563f},
    {0.991084924f, 0.008277483f, 0.000815573f}, {0.999999185f, 0.000000067f, 0.000177461f},
    {1.000000000f, 0.000000000f, 0.000105488f}, {0.999999999f, 0.000000000f, 0.000065311f},
    {0.999999988f, 0.000000000f, 0.000034730f}, {0.999999951f, 0.000000000f, 0.000032384f},
    {0.999999899f, 0.000000004f, 0.000012450f}, {0.999999811f, 0.000000010f, 0.000008285f},
    {0.999998922f, 0.000000025f, 0.000012059f}, {0.999994021f, 0.000000065f, 0.000009153f},
    {0.999954383f, 0.000001134f, 0.000017591f}, {0.999825195f, 0.000001533f, 0.000118782f},
    {0.999618187f, 0.000000940f, 0.000328111f}, {0.999266581f, 0.000009470f, 0.000656578f},
    {0.998698283f, 0.000056448f, 0.001165622f}, {0.998110564f, 0.000126909f, 0.001672347f},
    {0.997422502f, 0.000190122f, 0.002293204f}, {0.996722868f, 0.000264836f, 0.002918298f},
    {0.996045297f, 0.000334667f, 0.003566268f}, {0.995346684f, 0.000413773f, 0.004160554f},
    {0.994758251f, 0.000402274f, 0.004733066f}, {0.994229251f, 0.000416048f, 0.005237258f},
    {0.993734314f, 0.000374198f, 0.005787109f}, {0.993159673f, 0.000365093f, 0.006388126f},
    {0.992616287f, 0.000325574f, 0.006948119f}, {0.992188458f, 0.000295629f, 0.007422253f},
    {0.991881984f, 0.000234628f, 0.007818828f}, {0.991520838f, 0.000197638f, 0.008172359f},
    {0.991180331f, 0.000165582f, 0.008563685f}, {0.990911501f, 0.000138791f, 0.008859408f},
    {0.990713024f, 0.000125697f, 0.009061449f}, {0.990532233f, 0.000116913f, 0.009231764f},
    {0.990404275f, 0.000123074f, 0.009393334f}, {0.990288023f, 0.000144112f, 0.009448200f},
    {0.990183199f, 0.000170483f, 0.009528201f}, {0.990047857f, 0.000161374f, 0.009680004f},
    {0.989915503f, 0.000162754f, 0.009828152f}, {0.989861003f, 0.000137224f, 0.009919195f},
    {0.989851074f, 0.000129580f, 0.009904086f}, {0.989769619f, 0.000167975f, 0.009949906f},
    {0.989627951f, 0.000180551f, 0.010106495f}};

ccl_device RGBColor xyz_to_rgb(KernelGlobals *kg, float3 xyz)
{
  return make_float3(dot(float4_to_float3(kernel_data.film.xyz_to_r), xyz),
                     dot(float4_to_float3(kernel_data.film.xyz_to_g), xyz),
                     dot(float4_to_float3(kernel_data.film.xyz_to_b), xyz));
}

ccl_device float linear_rgb_to_gray(KernelGlobals *kg, float3 c)
{
  return dot(c, float4_to_float3(kernel_data.film.rgb_to_y));
}

ccl_device float3 find_position_in_lookup_unit_step(
    ccl_constant float lookup[][3], float position_to_find, int start, int end, int step)
{
  if (UNLIKELY(position_to_find <= start)) {
    return load_float3(lookup[0]);
  }
  if (UNLIKELY(position_to_find >= end)) {
    int i = (end - start) / step;
    return load_float3(lookup[i]);
  }

  float lookup_pos = (position_to_find - start) / (float)step;
  int lower_bound = floor_to_int(lookup_pos);
  int upper_bound = min(lower_bound + 1, (end - start) / step);
  float progress = lookup_pos - int(lookup_pos);
  return mix(load_float3(lookup[lower_bound]), load_float3(lookup[upper_bound]), progress);
}

ccl_device float find_position_in_lookup_unit_step(
    ccl_constant float lookup[], float position_to_find, int start, int end, int step)
{
  if (UNLIKELY(position_to_find <= start)) {
    return lookup[0];
  }
  if (UNLIKELY(position_to_find >= end)) {
    int i = (end - start) / step;
    return lookup[i];
  }

  float lookup_pos = (position_to_find - start) / (float)step;
  int lower_bound = floor_to_int(lookup_pos);
  int upper_bound = min(lower_bound + 1, (end - start) / step);
  float progress = lookup_pos - int(lookup_pos);
  return mix(lookup[lower_bound], lookup[upper_bound], progress);
}

ccl_device float3 wavelength_to_xyz(KernelGlobals *kg, float wavelength)
{
  int table_offset = kernel_data.cam.camera_response_function_table_offset;

  float position = lerp(
      0.0f, RAMP_TABLE_SIZE - 1.0f, inverse_lerp(MIN_WAVELENGTH, MAX_WAVELENGTH, wavelength));

  int lower_bound = floor_to_int(position);
  int upper_bound = min(lower_bound + 1, RAMP_TABLE_SIZE - 1);
  float progress = position - int(position);

  float3 lower_value = make_float3(
      kernel_tex_fetch(__lookup_table, table_offset + 3 * lower_bound + 0),
      kernel_tex_fetch(__lookup_table, table_offset + 3 * lower_bound + 1),
      kernel_tex_fetch(__lookup_table, table_offset + 3 * lower_bound + 2));
  float3 upper_value = make_float3(
      kernel_tex_fetch(__lookup_table, table_offset + 3 * upper_bound + 0),
      kernel_tex_fetch(__lookup_table, table_offset + 3 * upper_bound + 1),
      kernel_tex_fetch(__lookup_table, table_offset + 3 * upper_bound + 2));

  return lerp(lower_value, upper_value, progress);
  //   return
  //   find_position_in_lookup_unit_step(wavelength_xyz_lookup,
  //   wavelength, 360, 830, 1);
}

ccl_device RGBColor wavelength_intensities_to_linear(KernelGlobals *kg,
                                                     SpectralColor intensities,
                                                     SpectralColor wavelengths)
{
  RGBColor xyz_sum = make_float3(0.0f);
  FOR_EACH_CHANNEL(i)
  {
    RGBColor wavelength_xyz = wavelength_to_xyz(kg, wavelengths[i]);

    float wavelength_importance = lookup_table_read(
        kg,
        inverse_lerp(MIN_WAVELENGTH, MAX_WAVELENGTH, wavelengths[i]),
        kernel_data.cam.wavelength_importance_offset,
        RAMP_TABLE_SIZE);

    xyz_sum += wavelength_xyz * intensities[i] / wavelength_importance;
  }

  xyz_sum *= 3.0f / CHANNELS_PER_RAY;

  return xyz_to_rgb(kg, xyz_sum);
}

ccl_device SpectralColor linear_to_wavelength_intensities(RGBColor rgb, SpectralColor wavelengths)
{

  SpectralColor intensities;
  FOR_EACH_CHANNEL(i)
  {
    // find position in lookup of wavelength
    float3 magnitudes = find_position_in_lookup_unit_step(
        rec709_wavelength_lookup, wavelengths[i], 360, 830, 5);
    // multiply the lookups by the RGB factors
    float3 contributions = magnitudes * rgb;
    // add the three components
    intensities[i] = reduce_add_f(contributions);
  }

  return intensities;
}

CCL_NAMESPACE_END

#endif /* __KERNEL_COLOR_H__ */
