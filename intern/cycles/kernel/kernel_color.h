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

ccl_device float3 xyz_to_rgb(KernelGlobals *kg, float3 xyz)
{
  return make_float3(dot(float4_to_float3(kernel_data.film.xyz_to_r), xyz),
                     dot(float4_to_float3(kernel_data.film.xyz_to_g), xyz),
                     dot(float4_to_float3(kernel_data.film.xyz_to_b), xyz));
}

ccl_device float linear_rgb_to_gray(KernelGlobals *kg, float3 c)
{
  return dot(c, float4_to_float3(kernel_data.film.rgb_to_y));
}

ccl_device float float_lerp(float start, float end, float progress)
{
    return start + ((end - start) * progress);
}

ccl_device float3 wavelength_to_xyz(float wavelength)
{
    float4 wavelength_xyz_lookup[] = {
      make_float4(380.0f, 0.0014f, 0.0000f, 0.0065f),
      make_float4(381.0f, 0.0015f, 0.0000f, 0.0070f),
      make_float4(382.0f, 0.0016f, 0.0000f, 0.0077f),
      make_float4(383.0f, 0.0018f, 0.0001f, 0.0085f),
      make_float4(384.0f, 0.0020f, 0.0001f, 0.0094f),
      make_float4(385.0f, 0.0022f, 0.0001f, 0.0105f),
      make_float4(386.0f, 0.0025f, 0.0001f, 0.0120f),
      make_float4(387.0f, 0.0029f, 0.0001f, 0.0136f),
      make_float4(388.0f, 0.0033f, 0.0001f, 0.0155f),
      make_float4(389.0f, 0.0037f, 0.0001f, 0.0177f),
      make_float4(390.0f, 0.0042f, 0.0001f, 0.0201f),
      make_float4(391.0f, 0.0048f, 0.0001f, 0.0225f),
      make_float4(392.0f, 0.0053f, 0.0002f, 0.0252f),
      make_float4(393.0f, 0.0060f, 0.0002f, 0.0284f),
      make_float4(394.0f, 0.0068f, 0.0002f, 0.0320f),
      make_float4(395.0f, 0.0077f, 0.0002f, 0.0362f),
      make_float4(396.0f, 0.0088f, 0.0002f, 0.0415f),
      make_float4(397.0f, 0.0100f, 0.0003f, 0.0473f),
      make_float4(398.0f, 0.0113f, 0.0003f, 0.0536f),
      make_float4(399.0f, 0.0128f, 0.0004f, 0.0605f),
      make_float4(400.0f, 0.0143f, 0.0004f, 0.0679f),
      make_float4(401.0f, 0.0156f, 0.0004f, 0.0741f),
      make_float4(402.0f, 0.0171f, 0.0005f, 0.0810f),
      make_float4(403.0f, 0.0188f, 0.0005f, 0.0891f),
      make_float4(404.0f, 0.0208f, 0.0006f, 0.0988f),
      make_float4(405.0f, 0.0232f, 0.0006f, 0.1102f),
      make_float4(406.0f, 0.0263f, 0.0007f, 0.1249f),
      make_float4(407.0f, 0.0298f, 0.0008f, 0.1418f),
      make_float4(408.0f, 0.0339f, 0.0009f, 0.1612f),
      make_float4(409.0f, 0.0384f, 0.0011f, 0.1830f),
      make_float4(410.0f, 0.0435f, 0.0012f, 0.2074f),
      make_float4(411.0f, 0.0489f, 0.0014f, 0.2334f),
      make_float4(412.0f, 0.0550f, 0.0015f, 0.2625f),
      make_float4(413.0f, 0.0618f, 0.0017f, 0.2949f),
      make_float4(414.0f, 0.0693f, 0.0019f, 0.3311f),
      make_float4(415.0f, 0.0776f, 0.0022f, 0.3713f),
      make_float4(416.0f, 0.0871f, 0.0025f, 0.4170f),
      make_float4(417.0f, 0.0976f, 0.0028f, 0.4673f),
      make_float4(418.0f, 0.1089f, 0.0031f, 0.5221f),
      make_float4(419.0f, 0.1212f, 0.0035f, 0.5815f),
      make_float4(420.0f, 0.1344f, 0.0040f, 0.6456f),
      make_float4(421.0f, 0.1497f, 0.0046f, 0.7201f),
      make_float4(422.0f, 0.1657f, 0.0052f, 0.7980f),
      make_float4(423.0f, 0.1820f, 0.0058f, 0.8780f),
      make_float4(424.0f, 0.1985f, 0.0065f, 0.9588f),
      make_float4(425.0f, 0.2148f, 0.0073f, 1.0391f),
      make_float4(426.0f, 0.2299f, 0.0081f, 1.1141f),
      make_float4(427.0f, 0.2445f, 0.0089f, 1.1868f),
      make_float4(428.0f, 0.2584f, 0.0098f, 1.2566f),
      make_float4(429.0f, 0.2716f, 0.0107f, 1.3230f),
      make_float4(430.0f, 0.2839f, 0.0116f, 1.3856f),
      make_float4(431.0f, 0.2948f, 0.0126f, 1.4419f),
      make_float4(432.0f, 0.3047f, 0.0136f, 1.4939f),
      make_float4(433.0f, 0.3136f, 0.0146f, 1.5414f),
      make_float4(434.0f, 0.3216f, 0.0157f, 1.5844f),
      make_float4(435.0f, 0.3285f, 0.0168f, 1.6230f),
      make_float4(436.0f, 0.3343f, 0.0180f, 1.6561f),
      make_float4(437.0f, 0.3391f, 0.0192f, 1.6848f),
      make_float4(438.0f, 0.3430f, 0.0204f, 1.7094f),
      make_float4(439.0f, 0.3461f, 0.0217f, 1.7301f),
      make_float4(440.0f, 0.3483f, 0.0230f, 1.7471f),
      make_float4(441.0f, 0.3496f, 0.0243f, 1.7599f),
      make_float4(442.0f, 0.3501f, 0.0256f, 1.7695f),
      make_float4(443.0f, 0.3500f, 0.0270f, 1.7763f),
      make_float4(444.0f, 0.3493f, 0.0284f, 1.7805f),
      make_float4(445.0f, 0.3481f, 0.0298f, 1.7826f),
      make_float4(446.0f, 0.3464f, 0.0313f, 1.7833f),
      make_float4(447.0f, 0.3444f, 0.0329f, 1.7823f),
      make_float4(448.0f, 0.3420f, 0.0345f, 1.7800f),
      make_float4(449.0f, 0.3392f, 0.0362f, 1.7765f),
      make_float4(450.0f, 0.3362f, 0.0380f, 1.7721f),
      make_float4(451.0f, 0.3333f, 0.0398f, 1.7688f),
      make_float4(452.0f, 0.3301f, 0.0418f, 1.7647f),
      make_float4(453.0f, 0.3267f, 0.0438f, 1.7593f),
      make_float4(454.0f, 0.3229f, 0.0458f, 1.7525f),
      make_float4(455.0f, 0.3187f, 0.0480f, 1.7441f),
      make_float4(456.0f, 0.3140f, 0.0502f, 1.7335f),
      make_float4(457.0f, 0.3089f, 0.0526f, 1.7208f),
      make_float4(458.0f, 0.3033f, 0.0550f, 1.7060f),
      make_float4(459.0f, 0.2973f, 0.0574f, 1.6889f),
      make_float4(460.0f, 0.2908f, 0.0600f, 1.6692f),
      make_float4(461.0f, 0.2839f, 0.0626f, 1.6473f),
      make_float4(462.0f, 0.2766f, 0.0653f, 1.6226f),
      make_float4(463.0f, 0.2687f, 0.0680f, 1.5946f),
      make_float4(464.0f, 0.2602f, 0.0709f, 1.5632f),
      make_float4(465.0f, 0.2511f, 0.0739f, 1.5281f),
      make_float4(466.0f, 0.2406f, 0.0770f, 1.4849f),
      make_float4(467.0f, 0.2297f, 0.0803f, 1.4386f),
      make_float4(468.0f, 0.2184f, 0.0837f, 1.3897f),
      make_float4(469.0f, 0.2069f, 0.0872f, 1.3392f),
      make_float4(470.0f, 0.1954f, 0.0910f, 1.2876f),
      make_float4(471.0f, 0.1844f, 0.0949f, 1.2382f),
      make_float4(472.0f, 0.1735f, 0.0991f, 1.1887f),
      make_float4(473.0f, 0.1628f, 0.1034f, 1.1394f),
      make_float4(474.0f, 0.1523f, 0.1079f, 1.0904f),
      make_float4(475.0f, 0.1421f, 0.1126f, 1.0419f),
      make_float4(476.0f, 0.1322f, 0.1175f, 0.9943f),
      make_float4(477.0f, 0.1226f, 0.1226f, 0.9474f),
      make_float4(478.0f, 0.1133f, 0.1279f, 0.9015f),
      make_float4(479.0f, 0.1043f, 0.1334f, 0.8567f),
      make_float4(480.0f, 0.0956f, 0.1390f, 0.8130f),
      make_float4(481.0f, 0.0873f, 0.1446f, 0.7706f),
      make_float4(482.0f, 0.0793f, 0.1504f, 0.7296f),
      make_float4(483.0f, 0.0718f, 0.1564f, 0.6902f),
      make_float4(484.0f, 0.0646f, 0.1627f, 0.6523f),
      make_float4(485.0f, 0.0580f, 0.1693f, 0.6162f),
      make_float4(486.0f, 0.0519f, 0.1763f, 0.5825f),
      make_float4(487.0f, 0.0463f, 0.1836f, 0.5507f),
      make_float4(488.0f, 0.0412f, 0.1913f, 0.5205f),
      make_float4(489.0f, 0.0364f, 0.1994f, 0.4920f),
      make_float4(490.0f, 0.0320f, 0.2080f, 0.4652f),
      make_float4(491.0f, 0.0279f, 0.2171f, 0.4399f),
      make_float4(492.0f, 0.0241f, 0.2267f, 0.4162f),
      make_float4(493.0f, 0.0207f, 0.2368f, 0.3939f),
      make_float4(494.0f, 0.0175f, 0.2474f, 0.3730f),
      make_float4(495.0f, 0.0147f, 0.2586f, 0.3533f),
      make_float4(496.0f, 0.0121f, 0.2702f, 0.3349f),
      make_float4(497.0f, 0.0099f, 0.2824f, 0.3176f),
      make_float4(498.0f, 0.0079f, 0.2952f, 0.3014f),
      make_float4(499.0f, 0.0063f, 0.3087f, 0.2862f),
      make_float4(500.0f, 0.0049f, 0.3230f, 0.2720f),
      make_float4(501.0f, 0.0037f, 0.3385f, 0.2588f),
      make_float4(502.0f, 0.0029f, 0.3548f, 0.2464f),
      make_float4(503.0f, 0.0024f, 0.3717f, 0.2346f),
      make_float4(504.0f, 0.0022f, 0.3893f, 0.2233f),
      make_float4(505.0f, 0.0024f, 0.4073f, 0.2123f),
      make_float4(506.0f, 0.0029f, 0.4256f, 0.2010f),
      make_float4(507.0f, 0.0038f, 0.4443f, 0.1899f),
      make_float4(508.0f, 0.0052f, 0.4635f, 0.1790f),
      make_float4(509.0f, 0.0070f, 0.4830f, 0.1685f),
      make_float4(510.0f, 0.0093f, 0.5030f, 0.1582f),
      make_float4(511.0f, 0.0122f, 0.5237f, 0.1481f),
      make_float4(512.0f, 0.0156f, 0.5447f, 0.1384f),
      make_float4(513.0f, 0.0195f, 0.5658f, 0.1290f),
      make_float4(514.0f, 0.0240f, 0.5870f, 0.1201f),
      make_float4(515.0f, 0.0291f, 0.6082f, 0.1117f),
      make_float4(516.0f, 0.0349f, 0.6293f, 0.1040f),
      make_float4(517.0f, 0.0412f, 0.6502f, 0.0968f),
      make_float4(518.0f, 0.0480f, 0.6707f, 0.0901f),
      make_float4(519.0f, 0.0554f, 0.6906f, 0.0839f),
      make_float4(520.0f, 0.0633f, 0.7100f, 0.0782f),
      make_float4(521.0f, 0.0716f, 0.7280f, 0.0733f),
      make_float4(522.0f, 0.0805f, 0.7453f, 0.0687f),
      make_float4(523.0f, 0.0898f, 0.7619f, 0.0646f),
      make_float4(524.0f, 0.0995f, 0.7778f, 0.0608f),
      make_float4(525.0f, 0.1096f, 0.7932f, 0.0573f),
      make_float4(526.0f, 0.1202f, 0.8082f, 0.0539f),
      make_float4(527.0f, 0.1311f, 0.8225f, 0.0507f),
      make_float4(528.0f, 0.1423f, 0.8363f, 0.0477f),
      make_float4(529.0f, 0.1538f, 0.8495f, 0.0449f),
      make_float4(530.0f, 0.1655f, 0.8620f, 0.0422f),
      make_float4(531.0f, 0.1772f, 0.8738f, 0.0395f),
      make_float4(532.0f, 0.1891f, 0.8849f, 0.0369f),
      make_float4(533.0f, 0.2011f, 0.8955f, 0.0344f),
      make_float4(534.0f, 0.2133f, 0.9054f, 0.0321f),
      make_float4(535.0f, 0.2257f, 0.9149f, 0.0298f),
      make_float4(536.0f, 0.2383f, 0.9237f, 0.0277f),
      make_float4(537.0f, 0.2511f, 0.9321f, 0.0257f),
      make_float4(538.0f, 0.2640f, 0.9399f, 0.0238f),
      make_float4(539.0f, 0.2771f, 0.9472f, 0.0220f),
      make_float4(540.0f, 0.2904f, 0.9540f, 0.0203f),
      make_float4(541.0f, 0.3039f, 0.9602f, 0.0187f),
      make_float4(542.0f, 0.3176f, 0.9660f, 0.0172f),
      make_float4(543.0f, 0.3314f, 0.9712f, 0.0159f),
      make_float4(544.0f, 0.3455f, 0.9760f, 0.0146f),
      make_float4(545.0f, 0.3597f, 0.9803f, 0.0134f),
      make_float4(546.0f, 0.3741f, 0.9841f, 0.0123f),
      make_float4(547.0f, 0.3886f, 0.9874f, 0.0113f),
      make_float4(548.0f, 0.4034f, 0.9904f, 0.0104f),
      make_float4(549.0f, 0.4183f, 0.9929f, 0.0095f),
      make_float4(550.0f, 0.4334f, 0.9950f, 0.0087f),
      make_float4(551.0f, 0.4488f, 0.9967f, 0.0080f),
      make_float4(552.0f, 0.4644f, 0.9981f, 0.0074f),
      make_float4(553.0f, 0.4801f, 0.9992f, 0.0068f),
      make_float4(554.0f, 0.4960f, 0.9998f, 0.0062f),
      make_float4(555.0f, 0.5121f, 1.0000f, 0.0057f),
      make_float4(556.0f, 0.5283f, 0.9998f, 0.0053f),
      make_float4(557.0f, 0.5447f, 0.9993f, 0.0049f),
      make_float4(558.0f, 0.5612f, 0.9983f, 0.0045f),
      make_float4(559.0f, 0.5778f, 0.9969f, 0.0042f),
      make_float4(560.0f, 0.5945f, 0.9950f, 0.0039f),
      make_float4(561.0f, 0.6112f, 0.9926f, 0.0036f),
      make_float4(562.0f, 0.6280f, 0.9897f, 0.0034f),
      make_float4(563.0f, 0.6448f, 0.9865f, 0.0031f),
      make_float4(564.0f, 0.6616f, 0.9827f, 0.0029f),
      make_float4(565.0f, 0.6784f, 0.9786f, 0.0027f),
      make_float4(566.0f, 0.6953f, 0.9741f, 0.0026f),
      make_float4(567.0f, 0.7121f, 0.9692f, 0.0024f),
      make_float4(568.0f, 0.7288f, 0.9639f, 0.0023f),
      make_float4(569.0f, 0.7455f, 0.9581f, 0.0022f),
      make_float4(570.0f, 0.7621f, 0.9520f, 0.0021f),
      make_float4(571.0f, 0.7785f, 0.9454f, 0.0020f),
      make_float4(572.0f, 0.7948f, 0.9385f, 0.0019f),
      make_float4(573.0f, 0.8109f, 0.9312f, 0.0019f),
      make_float4(574.0f, 0.8268f, 0.9235f, 0.0018f),
      make_float4(575.0f, 0.8425f, 0.9154f, 0.0018f),
      make_float4(576.0f, 0.8579f, 0.9070f, 0.0018f),
      make_float4(577.0f, 0.8731f, 0.8983f, 0.0017f),
      make_float4(578.0f, 0.8879f, 0.8892f, 0.0017f),
      make_float4(579.0f, 0.9023f, 0.8798f, 0.0017f),
      make_float4(580.0f, 0.9163f, 0.8700f, 0.0017f),
      make_float4(581.0f, 0.9298f, 0.8598f, 0.0016f),
      make_float4(582.0f, 0.9428f, 0.8494f, 0.0016f),
      make_float4(583.0f, 0.9553f, 0.8386f, 0.0015f),
      make_float4(584.0f, 0.9672f, 0.8276f, 0.0015f),
      make_float4(585.0f, 0.9786f, 0.8163f, 0.0014f),
      make_float4(586.0f, 0.9894f, 0.8048f, 0.0013f),
      make_float4(587.0f, 0.9996f, 0.7931f, 0.0013f),
      make_float4(588.0f, 1.0091f, 0.7812f, 0.0012f),
      make_float4(589.0f, 1.0181f, 0.7692f, 0.0012f),
      make_float4(590.0f, 1.0263f, 0.7570f, 0.0011f),
      make_float4(591.0f, 1.0340f, 0.7448f, 0.0011f),
      make_float4(592.0f, 1.0410f, 0.7324f, 0.0011f),
      make_float4(593.0f, 1.0471f, 0.7200f, 0.0010f),
      make_float4(594.0f, 1.0524f, 0.7075f, 0.0010f),
      make_float4(595.0f, 1.0567f, 0.6949f, 0.0010f),
      make_float4(596.0f, 1.0597f, 0.6822f, 0.0010f),
      make_float4(597.0f, 1.0617f, 0.6695f, 0.0009f),
      make_float4(598.0f, 1.0628f, 0.6567f, 0.0009f),
      make_float4(599.0f, 1.0630f, 0.6439f, 0.0008f),
      make_float4(600.0f, 1.0622f, 0.6310f, 0.0008f),
      make_float4(601.0f, 1.0608f, 0.6182f, 0.0008f),
      make_float4(602.0f, 1.0585f, 0.6053f, 0.0007f),
      make_float4(603.0f, 1.0552f, 0.5925f, 0.0007f),
      make_float4(604.0f, 1.0509f, 0.5796f, 0.0006f),
      make_float4(605.0f, 1.0456f, 0.5668f, 0.0006f),
      make_float4(606.0f, 1.0389f, 0.5540f, 0.0005f),
      make_float4(607.0f, 1.0313f, 0.5411f, 0.0005f),
      make_float4(608.0f, 1.0226f, 0.5284f, 0.0004f),
      make_float4(609.0f, 1.0131f, 0.5157f, 0.0004f),
      make_float4(610.0f, 1.0026f, 0.5030f, 0.0003f),
      make_float4(611.0f, 0.9914f, 0.4905f, 0.0003f),
      make_float4(612.0f, 0.9794f, 0.4781f, 0.0003f),
      make_float4(613.0f, 0.9665f, 0.4657f, 0.0003f),
      make_float4(614.0f, 0.9529f, 0.4534f, 0.0003f),
      make_float4(615.0f, 0.9384f, 0.4412f, 0.0002f),
      make_float4(616.0f, 0.9232f, 0.4291f, 0.0002f),
      make_float4(617.0f, 0.9072f, 0.4170f, 0.0002f),
      make_float4(618.0f, 0.8904f, 0.4050f, 0.0002f),
      make_float4(619.0f, 0.8728f, 0.3930f, 0.0002f),
      make_float4(620.0f, 0.8544f, 0.3810f, 0.0002f),
      make_float4(621.0f, 0.8349f, 0.3689f, 0.0002f),
      make_float4(622.0f, 0.8148f, 0.3568f, 0.0002f),
      make_float4(623.0f, 0.7941f, 0.3447f, 0.0001f),
      make_float4(624.0f, 0.7729f, 0.3328f, 0.0001f),
      make_float4(625.0f, 0.7514f, 0.3210f, 0.0001f),
      make_float4(626.0f, 0.7296f, 0.3094f, 0.0001f),
      make_float4(627.0f, 0.7077f, 0.2979f, 0.0001f),
      make_float4(628.0f, 0.6858f, 0.2867f, 0.0001f),
      make_float4(629.0f, 0.6640f, 0.2757f, 0.0001f),
      make_float4(630.0f, 0.6424f, 0.2650f, 0.0000f),
      make_float4(631.0f, 0.6217f, 0.2548f, 0.0000f),
      make_float4(632.0f, 0.6013f, 0.2450f, 0.0000f),
      make_float4(633.0f, 0.5812f, 0.2354f, 0.0000f),
      make_float4(634.0f, 0.5614f, 0.2261f, 0.0000f),
      make_float4(635.0f, 0.5419f, 0.2170f, 0.0000f),
      make_float4(636.0f, 0.5226f, 0.2081f, 0.0000f),
      make_float4(637.0f, 0.5035f, 0.1995f, 0.0000f),
      make_float4(638.0f, 0.4847f, 0.1911f, 0.0000f),
      make_float4(639.0f, 0.4662f, 0.1830f, 0.0000f),
      make_float4(640.0f, 0.4479f, 0.1750f, 0.0000f),
      make_float4(641.0f, 0.4298f, 0.1672f, 0.0000f),
      make_float4(642.0f, 0.4121f, 0.1596f, 0.0000f),
      make_float4(643.0f, 0.3946f, 0.1523f, 0.0000f),
      make_float4(644.0f, 0.3775f, 0.1451f, 0.0000f),
      make_float4(645.0f, 0.3608f, 0.1382f, 0.0000f),
      make_float4(646.0f, 0.3445f, 0.1315f, 0.0000f),
      make_float4(647.0f, 0.3286f, 0.1250f, 0.0000f),
      make_float4(648.0f, 0.3131f, 0.1188f, 0.0000f),
      make_float4(649.0f, 0.2980f, 0.1128f, 0.0000f),
      make_float4(650.0f, 0.2835f, 0.1070f, 0.0000f),
      make_float4(651.0f, 0.2696f, 0.1015f, 0.0000f),
      make_float4(652.0f, 0.2562f, 0.0962f, 0.0000f),
      make_float4(653.0f, 0.2432f, 0.0911f, 0.0000f),
      make_float4(654.0f, 0.2307f, 0.0863f, 0.0000f),
      make_float4(655.0f, 0.2187f, 0.0816f, 0.0000f),
      make_float4(656.0f, 0.2071f, 0.0771f, 0.0000f),
      make_float4(657.0f, 0.1959f, 0.0728f, 0.0000f),
      make_float4(658.0f, 0.1852f, 0.0687f, 0.0000f),
      make_float4(659.0f, 0.1748f, 0.0648f, 0.0000f),
      make_float4(660.0f, 0.1649f, 0.0610f, 0.0000f),
      make_float4(661.0f, 0.1554f, 0.0574f, 0.0000f),
      make_float4(662.0f, 0.1462f, 0.0539f, 0.0000f),
      make_float4(663.0f, 0.1375f, 0.0507f, 0.0000f),
      make_float4(664.0f, 0.1291f, 0.0475f, 0.0000f),
      make_float4(665.0f, 0.1212f, 0.0446f, 0.0000f),
      make_float4(666.0f, 0.1136f, 0.0418f, 0.0000f),
      make_float4(667.0f, 0.1065f, 0.0391f, 0.0000f),
      make_float4(668.0f, 0.0997f, 0.0366f, 0.0000f),
      make_float4(669.0f, 0.0934f, 0.0342f, 0.0000f),
      make_float4(670.0f, 0.0874f, 0.0320f, 0.0000f),
      make_float4(671.0f, 0.0819f, 0.0300f, 0.0000f),
      make_float4(672.0f, 0.0768f, 0.0281f, 0.0000f),
      make_float4(673.0f, 0.0721f, 0.0263f, 0.0000f),
      make_float4(674.0f, 0.0677f, 0.0247f, 0.0000f),
      make_float4(675.0f, 0.0636f, 0.0232f, 0.0000f),
      make_float4(676.0f, 0.0598f, 0.0218f, 0.0000f),
      make_float4(677.0f, 0.0563f, 0.0205f, 0.0000f),
      make_float4(678.0f, 0.0529f, 0.0193f, 0.0000f),
      make_float4(679.0f, 0.0498f, 0.0181f, 0.0000f),
      make_float4(680.0f, 0.0468f, 0.0170f, 0.0000f),
      make_float4(681.0f, 0.0437f, 0.0159f, 0.0000f),
      make_float4(682.0f, 0.0408f, 0.0148f, 0.0000f),
      make_float4(683.0f, 0.0380f, 0.0138f, 0.0000f),
      make_float4(684.0f, 0.0354f, 0.0128f, 0.0000f),
      make_float4(685.0f, 0.0329f, 0.0119f, 0.0000f),
      make_float4(686.0f, 0.0306f, 0.0111f, 0.0000f),
      make_float4(687.0f, 0.0284f, 0.0103f, 0.0000f),
      make_float4(688.0f, 0.0264f, 0.0095f, 0.0000f),
      make_float4(689.0f, 0.0245f, 0.0088f, 0.0000f),
      make_float4(690.0f, 0.0227f, 0.0082f, 0.0000f),
      make_float4(691.0f, 0.0211f, 0.0076f, 0.0000f),
      make_float4(692.0f, 0.0196f, 0.0071f, 0.0000f),
      make_float4(693.0f, 0.0182f, 0.0066f, 0.0000f),
      make_float4(694.0f, 0.0170f, 0.0061f, 0.0000f),
      make_float4(695.0f, 0.0158f, 0.0057f, 0.0000f),
      make_float4(696.0f, 0.0148f, 0.0053f, 0.0000f),
      make_float4(697.0f, 0.0138f, 0.0050f, 0.0000f),
      make_float4(698.0f, 0.0129f, 0.0047f, 0.0000f),
      make_float4(699.0f, 0.0121f, 0.0044f, 0.0000f),
      make_float4(700.0f, 0.0114f, 0.0041f, 0.0000f),
      make_float4(701.0f, 0.0106f, 0.0038f, 0.0000f),
      make_float4(702.0f, 0.0099f, 0.0036f, 0.0000f),
      make_float4(703.0f, 0.0093f, 0.0034f, 0.0000f),
      make_float4(704.0f, 0.0087f, 0.0031f, 0.0000f),
      make_float4(705.0f, 0.0081f, 0.0029f, 0.0000f),
      make_float4(706.0f, 0.0076f, 0.0027f, 0.0000f),
      make_float4(707.0f, 0.0071f, 0.0026f, 0.0000f),
      make_float4(708.0f, 0.0066f, 0.0024f, 0.0000f),
      make_float4(709.0f, 0.0062f, 0.0022f, 0.0000f),
      make_float4(710.0f, 0.0058f, 0.0021f, 0.0000f),
      make_float4(711.0f, 0.0054f, 0.0020f, 0.0000f),
      make_float4(712.0f, 0.0051f, 0.0018f, 0.0000f),
      make_float4(713.0f, 0.0047f, 0.0017f, 0.0000f),
      make_float4(714.0f, 0.0044f, 0.0016f, 0.0000f),
      make_float4(715.0f, 0.0041f, 0.0015f, 0.0000f),
      make_float4(716.0f, 0.0038f, 0.0014f, 0.0000f),
      make_float4(717.0f, 0.0036f, 0.0013f, 0.0000f),
      make_float4(718.0f, 0.0033f, 0.0012f, 0.0000f),
      make_float4(719.0f, 0.0031f, 0.0011f, 0.0000f),
      make_float4(720.0f, 0.0029f, 0.0010f, 0.0000f),
      make_float4(721.0f, 0.0027f, 0.0010f, 0.0000f),
      make_float4(722.0f, 0.0025f, 0.0009f, 0.0000f),
      make_float4(723.0f, 0.0024f, 0.0008f, 0.0000f),
      make_float4(724.0f, 0.0022f, 0.0008f, 0.0000f),
      make_float4(725.0f, 0.0020f, 0.0007f, 0.0000f),
      make_float4(726.0f, 0.0019f, 0.0007f, 0.0000f),
      make_float4(727.0f, 0.0018f, 0.0006f, 0.0000f),
      make_float4(728.0f, 0.0017f, 0.0006f, 0.0000f),
      make_float4(729.0f, 0.0015f, 0.0006f, 0.0000f),
      make_float4(730.0f, 0.0014f, 0.0005f, 0.0000f),
      make_float4(731.0f, 0.0013f, 0.0005f, 0.0000f),
      make_float4(732.0f, 0.0012f, 0.0004f, 0.0000f),
      make_float4(733.0f, 0.0012f, 0.0004f, 0.0000f),
      make_float4(734.0f, 0.0011f, 0.0004f, 0.0000f),
      make_float4(735.0f, 0.0010f, 0.0004f, 0.0000f),
      make_float4(736.0f, 0.0009f, 0.0003f, 0.0000f),
      make_float4(737.0f, 0.0009f, 0.0003f, 0.0000f),
      make_float4(738.0f, 0.0008f, 0.0003f, 0.0000f),
      make_float4(739.0f, 0.0007f, 0.0003f, 0.0000f),
      make_float4(740.0f, 0.0007f, 0.0002f, 0.0000f),
      make_float4(741.0f, 0.0006f, 0.0002f, 0.0000f),
      make_float4(742.0f, 0.0006f, 0.0002f, 0.0000f),
      make_float4(743.0f, 0.0006f, 0.0002f, 0.0000f),
      make_float4(744.0f, 0.0005f, 0.0002f, 0.0000f),
      make_float4(745.0f, 0.0005f, 0.0002f, 0.0000f),
      make_float4(746.0f, 0.0004f, 0.0002f, 0.0000f),
      make_float4(747.0f, 0.0004f, 0.0001f, 0.0000f),
      make_float4(748.0f, 0.0004f, 0.0001f, 0.0000f),
      make_float4(749.0f, 0.0004f, 0.0001f, 0.0000f),
      make_float4(750.0f, 0.0003f, 0.0001f, 0.0000f),
      make_float4(751.0f, 0.0003f, 0.0001f, 0.0000f),
      make_float4(752.0f, 0.0003f, 0.0001f, 0.0000f),
      make_float4(753.0f, 0.0003f, 0.0001f, 0.0000f),
      make_float4(754.0f, 0.0003f, 0.0001f, 0.0000f),
      make_float4(755.0f, 0.0002f, 0.0001f, 0.0000f),
      make_float4(756.0f, 0.0002f, 0.0001f, 0.0000f),
      make_float4(757.0f, 0.0002f, 0.0001f, 0.0000f),
      make_float4(758.0f, 0.0002f, 0.0001f, 0.0000f),
      make_float4(759.0f, 0.0002f, 0.0001f, 0.0000f),
      make_float4(760.0f, 0.0002f, 0.0001f, 0.0000f),
      make_float4(761.0f, 0.0002f, 0.0001f, 0.0000f),
      make_float4(762.0f, 0.0001f, 0.0001f, 0.0000f),
      make_float4(763.0f, 0.0001f, 0.0000f, 0.0000f),
      make_float4(764.0f, 0.0001f, 0.0000f, 0.0000f),
      make_float4(765.0f, 0.0001f, 0.0000f, 0.0000f),
      make_float4(766.0f, 0.0001f, 0.0000f, 0.0000f),
      make_float4(767.0f, 0.0001f, 0.0000f, 0.0000f),
      make_float4(768.0f, 0.0001f, 0.0000f, 0.0000f),
      make_float4(769.0f, 0.0001f, 0.0000f, 0.0000f),
      make_float4(770.0f, 0.0001f, 0.0000f, 0.0000f),
      make_float4(771.0f, 0.0001f, 0.0000f, 0.0000f),
      make_float4(772.0f, 0.0001f, 0.0000f, 0.0000f),
      make_float4(773.0f, 0.0001f, 0.0000f, 0.0000f),
      make_float4(774.0f, 0.0001f, 0.0000f, 0.0000f),
      make_float4(775.0f, 0.0001f, 0.0000f, 0.0000f),
      make_float4(776.0f, 0.0001f, 0.0000f, 0.0000f),
      make_float4(777.0f, 0.0001f, 0.0000f, 0.0000f),
      make_float4(778.0f, 0.0000f, 0.0000f, 0.0000f),
      make_float4(779.0f, 0.0000f, 0.0000f, 0.0000f),
      make_float4(780.0f, 0.0000f, 0.0000f, 0.0000f)
    };
    int lower_bound = int(wavelength) - 380;
    int upper_bound = lower_bound + 1;
    float progress = wavelength - int(wavelength);
    return make_float3(
        float_lerp(wavelength_xyz_lookup[lower_bound][1], wavelength_xyz_lookup[upper_bound][1], progress),
        float_lerp(wavelength_xyz_lookup[lower_bound][2], wavelength_xyz_lookup[upper_bound][2], progress),
        float_lerp(wavelength_xyz_lookup[lower_bound][3], wavelength_xyz_lookup[upper_bound][3], progress)
    );
}

ccl_device float3 wavelength_intensities_to_linear(KernelGlobals *kg, float3 intensities, float3 wavelengths)
{
    float3 sum_x_xyz = wavelength_to_xyz(wavelengths.x) * intensities.x;
    float3 sum_y_xyz = wavelength_to_xyz(wavelengths.y) * intensities.y;
    float3 sum_z_xyz = wavelength_to_xyz(wavelengths.z) * intensities.z;
    float3 xyz_sum = sum_x_xyz + sum_y_xyz + sum_z_xyz;

    return xyz_to_rgb(kg, xyz_sum);
}

ccl_device float3 find_position_in_lookup(float4 lookup[], float wavelength)
{
    int upper_bound = 0;
    while(lookup[upper_bound][0] < wavelength) {
        upper_bound++;
    }
    int lower_bound = upper_bound -1;
    float progress = (wavelength - lookup[lower_bound][0]) / (lookup[upper_bound][0] - lookup[lower_bound][0]);
    return make_float3(
        float_lerp(lookup[lower_bound][1], lookup[upper_bound][1], progress),
        float_lerp(lookup[lower_bound][2], lookup[upper_bound][2], progress),
        float_lerp(lookup[lower_bound][3], lookup[upper_bound][3], progress)
    );
}

ccl_device float find_position_in_lookup_2d(float2 lookup[], float wavelength)
{
    int upper_bound = 0;
    while(lookup[upper_bound][0] < wavelength) {
        upper_bound++;
    }
    int lower_bound = upper_bound -1;
    float progress = (wavelength - lookup[lower_bound][0]) / (lookup[upper_bound][0] - lookup[lower_bound][0]);
    return float_lerp(lookup[lower_bound][1], lookup[upper_bound][1], progress);
}

ccl_device float3 linear_to_wavelength_intensities(float3 rgb, float3 wavelengths)
{
    float4 rec709_wavelength_lookup[] = {
      make_float4(380.0f, 0.021592459f, 0.010542406f, 0.967865135f),
      make_float4(390.0f, 0.020293111f, 0.010878976f, 0.968827912f),
      make_float4(400.0f, 0.021807906f, 0.011063512f, 0.967128582f),
      make_float4(410.0f, 0.023803297f, 0.010736566f, 0.965460137f),
      make_float4(420.0f, 0.025208132f, 0.011681813f, 0.963110055f),
      make_float4(430.0f, 0.025414957f, 0.012434719f, 0.962150324f),
      make_float4(440.0f, 0.024621282f, 0.014986907f, 0.960391811f),
      make_float4(450.0f, 0.020973705f, 0.020100392f, 0.958925903f),
      make_float4(460.0f, 0.015752802f, 0.030356263f, 0.953890935f),
      make_float4(470.0f, 0.01116804f, 0.063388962f, 0.925442998f),
      make_float4(480.0f, 0.008578277f, 0.173423837f, 0.817997886f),
      make_float4(490.0f, 0.006581877f, 0.568321142f, 0.42509696f),
      make_float4(500.0f, 0.005171723f, 0.827791998f, 0.167036273f),
      make_float4(510.0f, 0.004545205f, 0.916560468f, 0.078894327f),
      make_float4(520.0f, 0.00414512f, 0.952002841f, 0.043852038f),
      make_float4(530.0f, 0.004343112f, 0.964096452f, 0.031560435f),
      make_float4(540.0f, 0.005238155f, 0.970590861f, 0.024170984f),
      make_float4(550.0f, 0.007251939f, 0.972502542f, 0.020245519f),
      make_float4(560.0f, 0.012543656f, 0.969148203f, 0.01830814f),
      make_float4(570.0f, 0.028067132f, 0.955344651f, 0.016588218f),
      make_float4(580.0f, 0.091342277f, 0.892637233f, 0.01602049f),
      make_float4(590.0f, 0.484081092f, 0.5003641f, 0.015554808f),
      make_float4(600.0f, 0.870378324f, 0.116236717f, 0.013384959f),
      make_float4(610.0f, 0.939513128f, 0.047951391f, 0.012535491f),
      make_float4(620.0f, 0.960926994f, 0.027873526f, 0.011199484f),
      make_float4(630.0f, 0.968623763f, 0.020057963f, 0.011318274f),
      make_float4(640.0f, 0.971263883f, 0.017382174f, 0.011353953f),
      make_float4(650.0f, 0.972285819f, 0.015429109f, 0.012285073f),
      make_float4(660.0f, 0.971898742f, 0.01543808f, 0.012663188f),
      make_float4(670.0f, 0.972691859f, 0.014546826f, 0.012761325f),
      make_float4(680.0f, 0.971734812f, 0.015197773f, 0.013067426f),
      make_float4(690.0f, 0.97234454f, 0.014285896f, 0.013369566f),
      make_float4(700.0f, 0.97150339f, 0.015069123f, 0.013427487f),
      make_float4(710.0f, 0.970857997f, 0.015506263f, 0.01363574f),
      make_float4(720.0f, 0.970553866f, 0.015545797f, 0.013893597f),
      make_float4(730.0f, 0.969671404f, 0.016302839f, 0.014025757f),
    };
    // find position in lookup of first wavelength
    float3 wavelength_one_magnitudes = find_position_in_lookup(rec709_wavelength_lookup, wavelengths[0]);
    // multiply the lookups by the RGB factors
    float3 contributions_one = wavelength_one_magnitudes * rgb;
    // add the three components
    float wavelength_one_brightness = contributions_one[0] + contributions_one[1] + contributions_one[2];

    // repeat for other two wavelengths
    float3 wavelength_two_magnitudes = find_position_in_lookup(rec709_wavelength_lookup, wavelengths[1]);
    float3 contributions_two = wavelength_two_magnitudes * rgb;
    float wavelength_two_brightness = contributions_two[0] + contributions_two[1] + contributions_two[2];

    float3 wavelength_three_magnitudes = find_position_in_lookup(rec709_wavelength_lookup, wavelengths[2]);
    float3 contributions_three = wavelength_three_magnitudes * rgb;
    float wavelength_three_brightness = contributions_three[0] + contributions_three[1] + contributions_three[2];

    return make_float3(
        wavelength_one_brightness,
        wavelength_two_brightness,
        wavelength_three_brightness
    );
}

CCL_NAMESPACE_END

#endif /* __KERNEL_COLOR_H__ */
