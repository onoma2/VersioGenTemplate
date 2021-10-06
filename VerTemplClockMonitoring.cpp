#include "VerTemplClockMonitoring.h"

namespace VerTemplClockMonitoring {

/*******************************************************************************************************************
Cycling '74 License for Max-Generated Code for Export
Copyright (c) 2016 Cycling '74
The code that Max generates automatically and that end users are capable of exporting and using, and any
  associated documentation files (the “Software”) is a work of authorship for which Cycling '74 is the author
  and owner for copyright purposes.  A license is hereby granted, free of charge, to any person obtaining a
  copy of the Software (“Licensee”) to use, copy, modify, merge, publish, and distribute copies of the Software,
  and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The Software is licensed to Licensee only for non-commercial use. Users who wish to make commercial use of the
  Software must contact the copyright owner to determine if a license for commercial use is available, and the
  terms and conditions for same, which may include fees or royalties. For commercial use, please send inquiries
  to licensing (at) cycling74.com.  The determination of whether a use is commercial use or non-commercial use is based
  upon the use, not the user. The Software may be used by individuals, institutions, governments, corporations, or
  other business whether for-profit or non-profit so long as the use itself is not a commercialization of the
  materials or a use that generates or is intended to generate income, revenue, sales or profit.
The above copyright notice and this license shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*******************************************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Data m_sample_18;
	Delta __m_delta_24;
	Delta __m_delta_34;
	Phasor __m_phasor_35;
	Phasor __m_phasor_33;
	PlusEquals __m_pluseq_26;
	Rate __m_rate_36;
	Sah __m_sah_37;
	int __exception;
	int vectorsize;
	t_sample __m_count_25;
	t_sample m_history_7;
	t_sample m_history_2;
	t_sample m_history_3;
	t_sample m_sw_23;
	t_sample __m_count_27;
	t_sample __m_latch_28;
	t_sample __m_slide_30;
	t_sample samplerate;
	t_sample m_ctrl_22;
	t_sample m_history_1;
	t_sample samples_to_seconds;
	t_sample m_history_6;
	t_sample m_ctrl_21;
	t_sample m_ctrl_19;
	t_sample m_history_11;
	t_sample m_sw_12;
	t_sample m_history_10;
	t_sample m_history_8;
	t_sample m_history_9;
	t_sample m_ctrl_20;
	t_sample m_gate_13;
	t_sample m_ctrl_15;
	t_sample m_history_4;
	t_sample m_button_14;
	t_sample m_ctrl_17;
	t_sample m_history_5;
	t_sample m_ctrl_16;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_history_2 = ((int)0);
		m_history_3 = ((int)0);
		m_history_4 = ((int)0);
		m_history_5 = ((int)0);
		m_history_6 = ((int)0);
		m_history_7 = ((int)0);
		m_history_8 = ((int)0);
		m_history_9 = ((int)0);
		m_history_10 = ((int)0);
		m_history_11 = ((int)0);
		m_sw_12 = ((int)0);
		m_gate_13 = ((int)0);
		m_button_14 = ((int)0);
		m_ctrl_15 = ((int)0);
		m_ctrl_16 = ((int)0);
		m_ctrl_17 = ((int)0);
		m_sample_18.reset("sample", ((int)196000), ((int)1));
		m_ctrl_19 = ((int)0);
		m_ctrl_20 = ((int)0);
		m_ctrl_21 = ((int)0);
		m_ctrl_22 = ((int)0);
		m_sw_23 = ((int)0);
		__m_delta_24.reset(0);
		__m_count_25 = 0;
		__m_pluseq_26.reset(0);
		__m_count_27 = 0;
		__m_latch_28 = 0;
		__m_slide_30 = 0;
		samples_to_seconds = (1 / samplerate);
		__m_phasor_33.reset(0);
		__m_delta_34.reset(0);
		__m_phasor_35.reset(0);
		__m_rate_36.reset();
		__m_sah_37.reset(0);
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		t_sample * __out3 = __outs[2];
		t_sample * __out4 = __outs[3];
		t_sample * __out5 = __outs[4];
		t_sample * __out6 = __outs[5];
		t_sample * __out7 = __outs[6];
		t_sample * __out8 = __outs[7];
		t_sample * __out9 = __outs[8];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) || (__out4 == 0) || (__out5 == 0) || (__out6 == 0) || (__out7 == 0) || (__out8 == 0) || (__out9 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		int sample_dim = m_sample_18.dim;
		int sample_channels = m_sample_18.channels;
		int sample_dim_151 = sample_dim;
		int or_47 = (m_gate_13 || m_button_14);
		t_sample iup_31 = (1 / maximum(1, abs(((int)300))));
		t_sample idown_32 = (1 / maximum(1, abs(((int)300))));
		samples_to_seconds = (1 / samplerate);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample out3 = ((int)0);
			t_sample out5 = ((int)0);
			t_sample out4 = ((int)0);
			t_sample out6 = ((int)0);
			t_sample out9 = ((int)0);
			t_sample out8 = ((int)0);
			t_sample out7 = ((int)0);
			int delta_165 = __m_delta_24(or_47);
			int gtep_164 = ((delta_165 >= ((int)1)) ? delta_165 : 0);
			__m_count_25 = (gtep_164 ? 0 : (fixdenorm(__m_count_25 + ((int)1))));
			int counter_154 = __m_count_25;
			int counter_155 = ((int)0);
			int counter_156 = ((int)0);
			t_sample plusequals_163 = __m_pluseq_26.post(gtep_164, m_history_11, 0);
			int eq_161 = (plusequals_163 == ((int)2));
			__m_count_27 = (m_history_11 ? 0 : (fixdenorm(__m_count_27 + plusequals_163)));
			t_sample counter_158 = __m_count_27;
			int counter_159 = ((int)0);
			int counter_160 = ((int)0);
			__m_latch_28 = ((eq_161 != 0) ? counter_158 : __m_latch_28);
			t_sample latch_157 = __m_latch_28;
			t_sample gen_167 = latch_157;
			t_sample history_162_next_166 = fixdenorm(eq_161);
			bool index_ignore_29 = ((counter_154 >= sample_dim) || (counter_154 < 0));
			if ((!index_ignore_29)) {
				m_sample_18.write(in1, counter_154, 0);
				
			};
			t_sample mix_1471 = (m_history_10 + (((t_sample)0.0042742627044161) * (m_ctrl_17 - m_history_10)));
			t_sample mix_19 = mix_1471;
			t_sample mix_1472 = (m_history_9 + (((t_sample)0.0042742627044161) * (mix_19 - m_history_9)));
			t_sample mix_17 = mix_1472;
			t_sample mix_1473 = (m_history_8 + (((t_sample)0.0042742627044161) * (mix_17 - m_history_8)));
			t_sample mix_15 = mix_1473;
			t_sample gen_31 = mix_15;
			t_sample history_20_next_22 = fixdenorm(mix_19);
			t_sample history_18_next_23 = fixdenorm(mix_17);
			t_sample history_16_next_24 = fixdenorm(mix_15);
			t_sample div_148 = safediv(gen_167, sample_dim_151);
			t_sample div_143 = safediv(gen_167, samplerate);
			t_sample rdiv_144 = safediv(((int)1), div_143);
			t_sample mix_1474 = (m_history_7 + (((t_sample)0.0042742627044161) * (m_ctrl_22 - m_history_7)));
			t_sample mix_1433 = mix_1474;
			t_sample mix_1475 = (m_history_6 + (((t_sample)0.0042742627044161) * (mix_1433 - m_history_6)));
			t_sample mix_1439 = mix_1475;
			t_sample mix_1476 = (m_history_5 + (((t_sample)0.0042742627044161) * (mix_1439 - m_history_5)));
			t_sample mix_1437 = mix_1476;
			t_sample gen_29 = mix_1437;
			t_sample history_20_next_1441 = fixdenorm(mix_1433);
			t_sample history_18_next_1434 = fixdenorm(mix_1439);
			t_sample history_16_next_1436 = fixdenorm(mix_1437);
			t_sample mul_123 = (gen_29 * ((t_sample)1.1));
			int int_124 = int(mul_123);
			t_sample mix_1477 = (m_history_4 + (((t_sample)0.0042742627044161) * (m_ctrl_19 - m_history_4)));
			t_sample mix_1446 = mix_1477;
			t_sample mix_1478 = (m_history_3 + (((t_sample)0.0042742627044161) * (mix_1446 - m_history_3)));
			t_sample mix_1452 = mix_1478;
			t_sample mix_1479 = (m_history_2 + (((t_sample)0.0042742627044161) * (mix_1452 - m_history_2)));
			t_sample mix_1450 = mix_1479;
			t_sample gen_28 = mix_1450;
			t_sample history_20_next_1454 = fixdenorm(mix_1446);
			t_sample history_18_next_1447 = fixdenorm(mix_1452);
			t_sample history_16_next_1449 = fixdenorm(mix_1450);
			t_sample MOD_245 = gen_28;
			__m_slide_30 = fixdenorm((__m_slide_30 + (((MOD_245 > __m_slide_30) ? iup_31 : idown_32) * (MOD_245 - __m_slide_30))));
			t_sample slide_122 = __m_slide_30;
			t_sample mul_127 = (slide_122 * ((int)7));
			int int_130 = int(mul_127);
			t_sample pow_129 = safepow(((int)2), int_130);
			t_sample slices_132 = pow_129;
			t_sample slices_134 = slices_132;
			t_sample mul_142 = (rdiv_144 * slices_134);
			t_sample phasor_145 = __m_phasor_33(mul_142, samples_to_seconds);
			t_sample delta_136 = __m_delta_34(phasor_145);
			t_sample div_137 = safediv(m_history_1, slices_132);
			t_sample phasor_679 = __m_phasor_35(((int)440), samples_to_seconds);
			t_sample rate_885 = __m_rate_36.perform_off(phasor_679, ((int)48000));
			t_sample clamp_146 = ((rate_885 <= ((int)0)) ? ((int)0) : ((rate_885 >= ((t_sample)0.99)) ? ((t_sample)0.99) : rate_885));
			t_sample sah_147 = __m_sah_37(clamp_146, delta_136, ((int)0));
			t_sample mul_140 = (sah_147 * slices_132);
			int int_139 = int(mul_140);
			t_sample div_138 = safediv(int_139, slices_132);
			t_sample add_141 = (div_138 + div_137);
			t_sample rsub_126 = (((int)1) - add_141);
			t_sample mix_1480 = (add_141 + (int_124 * (rsub_126 - add_141)));
			t_sample mul_149 = (mix_1480 * div_148);
			double sample_index_38 = (mul_149 * (sample_dim - 1));
			int index_trunc_39 = fixnan(floor(sample_index_38));
			bool index_ignore_40 = ((index_trunc_39 >= sample_dim) || (index_trunc_39 < 0));
			// phase sample channel 1;
			t_sample sample_sample_169 = (index_ignore_40 ? 0 : m_sample_18.read(index_trunc_39, 0));
			t_sample index_sample_170 = sample_index_38;
			t_sample mix_1481 = (in1 + (gen_31 * (sample_sample_169 - in1)));
			t_sample out2 = mix_1481;
			t_sample out1 = mix_1481;
			t_sample history_135_next_1459 = fixdenorm(phasor_145);
			m_history_11 = history_162_next_166;
			m_history_10 = history_20_next_22;
			m_history_8 = history_16_next_24;
			m_history_9 = history_18_next_23;
			m_history_7 = history_20_next_1441;
			m_history_5 = history_16_next_1436;
			m_history_6 = history_18_next_1434;
			m_history_4 = history_20_next_1454;
			m_history_2 = history_16_next_1449;
			m_history_3 = history_18_next_1447;
			m_history_1 = history_135_next_1459;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			(*(__out4++)) = out4;
			(*(__out5++)) = out5;
			(*(__out6++)) = out6;
			(*(__out7++)) = out7;
			(*(__out8++)) = out8;
			(*(__out9++)) = out9;
			
		};
		return __exception;
		
	};
	inline void set_sw2(t_param _value) {
		m_sw_12 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_gate(t_param _value) {
		m_gate_13 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_button(t_param _value) {
		m_button_14 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl5(t_param _value) {
		m_ctrl_15 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl6(t_param _value) {
		m_ctrl_16 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl1(t_param _value) {
		m_ctrl_17 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sample(void * _value) {
		m_sample_18.setbuffer(_value);
	};
	inline void set_ctrl2(t_param _value) {
		m_ctrl_19 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl7(t_param _value) {
		m_ctrl_20 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl4(t_param _value) {
		m_ctrl_21 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl3(t_param _value) {
		m_ctrl_22 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_23 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 9;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 12; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2" };
const char *gen_kernel_outnames[] = { "out1", "out2", "led1", "led2", "led3", "led4", "out7", "out8", "out9" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_button(value); break;
		case 1: self->set_ctrl1(value); break;
		case 2: self->set_ctrl2(value); break;
		case 3: self->set_ctrl3(value); break;
		case 4: self->set_ctrl4(value); break;
		case 5: self->set_ctrl5(value); break;
		case 6: self->set_ctrl6(value); break;
		case 7: self->set_ctrl7(value); break;
		case 8: self->set_gate(value); break;
		case 9: self->set_sample(ref); break;
		case 10: self->set_sw1(value); break;
		case 11: self->set_sw2(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_button_14; break;
		case 1: *value = self->m_ctrl_17; break;
		case 2: *value = self->m_ctrl_19; break;
		case 3: *value = self->m_ctrl_22; break;
		case 4: *value = self->m_ctrl_21; break;
		case 5: *value = self->m_ctrl_15; break;
		case 6: *value = self->m_ctrl_16; break;
		case 7: *value = self->m_ctrl_20; break;
		case 8: *value = self->m_gate_13; break;
		
		case 10: *value = self->m_sw_23; break;
		case 11: *value = self->m_sw_12; break;
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(12 * sizeof(ParamInfo));
	self->__commonstate.numparams = 12;
	// initialize parameter 0 ("m_button_14")
	pi = self->__commonstate.params + 0;
	pi->name = "button";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_button_14;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_ctrl_17")
	pi = self->__commonstate.params + 1;
	pi->name = "ctrl1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_17;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_ctrl_19")
	pi = self->__commonstate.params + 2;
	pi->name = "ctrl2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_19;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_ctrl_22")
	pi = self->__commonstate.params + 3;
	pi->name = "ctrl3";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_22;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_ctrl_21")
	pi = self->__commonstate.params + 4;
	pi->name = "ctrl4";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_21;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_ctrl_15")
	pi = self->__commonstate.params + 5;
	pi->name = "ctrl5";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_15;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_ctrl_16")
	pi = self->__commonstate.params + 6;
	pi->name = "ctrl6";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_16;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_ctrl_20")
	pi = self->__commonstate.params + 7;
	pi->name = "ctrl7";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_20;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_gate_13")
	pi = self->__commonstate.params + 8;
	pi->name = "gate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_gate_13;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_sample_18")
	pi = self->__commonstate.params + 9;
	pi->name = "sample";
	pi->paramtype = GENLIB_PARAMTYPE_SYM;
	pi->defaultvalue = 0.;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = false;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 10 ("m_sw_23")
	pi = self->__commonstate.params + 10;
	pi->name = "sw1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_23;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_sw_12")
	pi = self->__commonstate.params + 11;
	pi->name = "sw2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_12;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // VerTemplClockMonitoring::
