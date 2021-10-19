#include "GiveTitle.h"

namespace GiveTitle {

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
	Data m_main_20;
	Delta __m_delta_29;
	PlusEquals __m_pluseq_30;
	Rate __m_rate_28;
	int __exception;
	int vectorsize;
	t_sample m_sw_18;
	t_sample m_button_17;
	t_sample m_gate_16;
	t_sample m_sw_19;
	t_sample m_ctrl_22;
	t_sample m_ctrl_15;
	t_sample m_ctrl_21;
	t_sample __m_carry_25;
	t_sample __m_count_23;
	t_sample m_ctrl_14;
	t_sample m_ctrl_13;
	t_sample m_ctrl_12;
	t_sample m_history_3;
	t_sample m_history_4;
	t_sample m_history_2;
	t_sample samplerate;
	t_sample m_history_1;
	t_sample __m_count_31;
	t_sample m_history_5;
	t_sample m_history_7;
	t_sample m_ctrl_11;
	t_sample m_history_6;
	t_sample m_history_10;
	t_sample m_history_8;
	t_sample m_history_9;
	t_sample __m_latch_32;
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
		m_ctrl_11 = ((int)0);
		m_ctrl_12 = ((int)0);
		m_ctrl_13 = ((int)0);
		m_ctrl_14 = ((int)0);
		m_ctrl_15 = ((int)0);
		m_gate_16 = ((int)0);
		m_button_17 = ((int)0);
		m_sw_18 = ((int)0);
		m_sw_19 = ((int)0);
		m_main_20.reset("main", ((int)768000), ((int)2));
		m_ctrl_21 = ((int)0);
		m_ctrl_22 = ((int)0);
		__m_count_23 = 0;
		__m_carry_25 = 0;
		__m_rate_28.reset();
		__m_delta_29.reset(0);
		__m_pluseq_30.reset(0);
		__m_count_31 = 0;
		__m_latch_32 = 0;
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
		t_sample * __out10 = __outs[9];
		t_sample * __out11 = __outs[10];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) || (__out4 == 0) || (__out5 == 0) || (__out6 == 0) || (__out7 == 0) || (__out8 == 0) || (__out9 == 0) || (__out10 == 0) || (__out11 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		int main_dim = m_main_20.dim;
		int main_channels = m_main_20.channels;
		int dim_175 = main_dim;
		int dim_23 = main_dim;
		int orange_1840 = (dim_175 - ((int)96000));
		int irange_1843 = (dim_23 - ((int)1));
		int or_114 = (m_gate_16 || m_button_17);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample out5 = ((int)0);
			t_sample out3 = ((int)0);
			t_sample out4 = ((int)0);
			t_sample out6 = ((int)0);
			t_sample out7 = ((int)0);
			t_sample out11 = samplerate;
			t_sample mix_1832 = (m_history_10 + (((t_sample)0.0042742627044161) * (m_ctrl_15 - m_history_10)));
			t_sample mix_73 = mix_1832;
			t_sample mix_1833 = (m_history_9 + (((t_sample)0.0042742627044161) * (mix_73 - m_history_9)));
			t_sample mix_71 = mix_1833;
			t_sample mix_1834 = (m_history_8 + (((t_sample)0.0042742627044161) * (mix_71 - m_history_8)));
			t_sample mix_69 = mix_1834;
			t_sample gen_94 = mix_69;
			t_sample history_74_next_80 = fixdenorm(mix_73);
			t_sample history_72_next_81 = fixdenorm(mix_71);
			t_sample history_70_next_82 = fixdenorm(mix_69);
			int lt_182 = (gen_94 < ((t_sample)0.99));
			t_sample switch_180 = (lt_182 ? in1 : ((int)0));
			t_sample mix_1835 = (m_history_7 + (((t_sample)0.0042742627044161) * (m_ctrl_13 - m_history_7)));
			t_sample mix_1749 = mix_1835;
			t_sample mix_1836 = (m_history_6 + (((t_sample)0.0042742627044161) * (mix_1749 - m_history_6)));
			t_sample mix_1758 = mix_1836;
			t_sample mix_1837 = (m_history_5 + (((t_sample)0.0042742627044161) * (mix_1758 - m_history_5)));
			t_sample mix_1753 = mix_1837;
			t_sample gen_92 = mix_1753;
			t_sample history_74_next_1757 = fixdenorm(mix_1749);
			t_sample history_72_next_1755 = fixdenorm(mix_1758);
			t_sample history_70_next_1754 = fixdenorm(mix_1753);
			t_sample sub_1841 = (gen_92 - ((int)0));
			t_sample scale_1838 = ((safepow((sub_1841 * ((t_sample)1)), ((int)1)) * orange_1840) + ((int)96000));
			__m_count_23 = (((int)0) ? 0 : (fixdenorm(__m_count_23 + ((int)1))));
			int carry_24 = 0;
			if ((((int)0) != 0)) {
				__m_count_23 = 0;
				__m_carry_25 = 0;
				
			} else if (((scale_1838 > 0) && (__m_count_23 >= scale_1838))) {
				int wraps_26 = (__m_count_23 / scale_1838);
				__m_carry_25 = (__m_carry_25 + wraps_26);
				__m_count_23 = (__m_count_23 - (wraps_26 * scale_1838));
				carry_24 = 1;
				
			};
			int counter_16 = __m_count_23;
			int counter_17 = carry_24;
			int counter_18 = __m_carry_25;
			int switch_181 = (lt_182 ? counter_16 : ((int)0));
			int index_wrap_27 = ((switch_181 < 0) ? ((main_dim - 1) + ((switch_181 + 1) % main_dim)) : (switch_181 % main_dim));
			m_main_20.write(switch_180, index_wrap_27, 0);
			int sub_1845 = (counter_16 - ((int)1));
			t_sample scale_1842 = ((safepow(safediv(sub_1845, irange_1843), ((int)1)) * ((int)1)) + ((int)0));
			t_sample rate_28 = __m_rate_28.perform_off(scale_1842, ((int)1));
			t_sample out9 = rate_28;
			t_sample mix_1846 = (m_history_4 + (((t_sample)0.0042742627044161) * (m_ctrl_11 - m_history_4)));
			t_sample mix_1763 = mix_1846;
			t_sample mix_1847 = (m_history_3 + (((t_sample)0.0042742627044161) * (mix_1763 - m_history_3)));
			t_sample mix_1767 = mix_1847;
			t_sample mix_1848 = (m_history_2 + (((t_sample)0.0042742627044161) * (mix_1767 - m_history_2)));
			t_sample mix_1762 = mix_1848;
			t_sample gen_90 = mix_1762;
			t_sample history_74_next_1771 = fixdenorm(mix_1763);
			t_sample history_72_next_1769 = fixdenorm(mix_1767);
			t_sample history_70_next_1768 = fixdenorm(mix_1762);
			t_sample add_3 = (gen_90 + ((t_sample)0.001));
			t_sample mul_1511 = (add_3 * ((int)16));
			t_sample ceil_6 = ceil(mul_1511);
			t_sample out8 = ceil_6;
			int delta_107 = __m_delta_29(or_114);
			int gtep_106 = ((delta_107 >= ((int)1)) ? delta_107 : 0);
			t_sample plusequals_105 = __m_pluseq_30.post(gtep_106, m_history_1, 0);
			int eq_103 = (plusequals_105 == ((int)2));
			__m_count_31 = (m_history_1 ? 0 : (fixdenorm(__m_count_31 + plusequals_105)));
			t_sample counter_100 = __m_count_31;
			int counter_101 = ((int)0);
			int counter_102 = ((int)0);
			__m_latch_32 = ((eq_103 != 0) ? counter_100 : __m_latch_32);
			t_sample latch_99 = __m_latch_32;
			t_sample history_104_next_111 = fixdenorm(eq_103);
			t_sample div_9 = safediv(latch_99, ceil_6);
			t_sample div_4 = safediv(div_9, scale_1838);
			t_sample mod_8 = safemod(rate_28, div_4);
			t_sample out10 = mod_8;
			double sample_index_33 = (mod_8 * main_dim);
			int index_trunc_34 = fixnan(floor(sample_index_33));
			double index_fract_35 = (sample_index_33 - index_trunc_34);
			int index_trunc_36 = (index_trunc_34 - 1);
			int index_trunc_37 = (index_trunc_34 + 1);
			int index_trunc_38 = (index_trunc_34 + 2);
			int index_wrap_39 = ((index_trunc_36 < 0) ? ((main_dim - 1) + ((index_trunc_36 + 1) % main_dim)) : (index_trunc_36 % main_dim));
			int index_wrap_40 = ((index_trunc_34 < 0) ? ((main_dim - 1) + ((index_trunc_34 + 1) % main_dim)) : (index_trunc_34 % main_dim));
			int index_wrap_41 = ((index_trunc_37 < 0) ? ((main_dim - 1) + ((index_trunc_37 + 1) % main_dim)) : (index_trunc_37 % main_dim));
			int index_wrap_42 = ((index_trunc_38 < 0) ? ((main_dim - 1) + ((index_trunc_38 + 1) % main_dim)) : (index_trunc_38 % main_dim));
			// phase main channel 1;
			double read_main_43 = m_main_20.read(index_wrap_39, 0);
			double read_main_44 = m_main_20.read(index_wrap_40, 0);
			double read_main_45 = m_main_20.read(index_wrap_41, 0);
			double read_main_46 = m_main_20.read(index_wrap_42, 0);
			double readinterp_47 = spline_interp(index_fract_35, read_main_43, read_main_44, read_main_45, read_main_46);
			t_sample sample_main_172 = readinterp_47;
			t_sample index_main_173 = sample_index_33;
			t_sample mul_34 = (mod_8 * ((int)2));
			t_sample sub_33 = (mul_34 - ((int)1));
			t_sample cos_32 = cos(sub_33);
			t_sample sub_31 = (cos_32 - ((t_sample)0.5));
			t_sample mul_30 = (sub_31 * ((int)10));
			t_sample clamp_29 = ((mul_30 <= ((int)0)) ? ((int)0) : ((mul_30 >= ((int)1)) ? ((int)1) : mul_30));
			t_sample mul_1 = (sample_main_172 * clamp_29);
			t_sample mix_1849 = (((int)0) + (((t_sample)0.5) * (mul_1 - ((int)0))));
			t_sample mix_1850 = (in1 + (gen_94 * (mix_1849 - in1)));
			t_sample out2 = mix_1850;
			t_sample out1 = mix_1850;
			m_history_10 = history_74_next_80;
			m_history_8 = history_70_next_82;
			m_history_9 = history_72_next_81;
			m_history_7 = history_74_next_1757;
			m_history_5 = history_70_next_1754;
			m_history_6 = history_72_next_1755;
			m_history_4 = history_74_next_1771;
			m_history_2 = history_70_next_1768;
			m_history_3 = history_72_next_1769;
			m_history_1 = history_104_next_111;
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
			(*(__out10++)) = out10;
			(*(__out11++)) = out11;
			
		};
		return __exception;
		
	};
	inline void set_ctrl3(t_param _value) {
		m_ctrl_11 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl7(t_param _value) {
		m_ctrl_12 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl5(t_param _value) {
		m_ctrl_13 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl4(t_param _value) {
		m_ctrl_14 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl1(t_param _value) {
		m_ctrl_15 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_gate(t_param _value) {
		m_gate_16 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_button(t_param _value) {
		m_button_17 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_18 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw2(t_param _value) {
		m_sw_19 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_main(void * _value) {
		m_main_20.setbuffer(_value);
	};
	inline void set_ctrl6(t_param _value) {
		m_ctrl_21 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl2(t_param _value) {
		m_ctrl_22 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 11;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 12; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2" };
const char *gen_kernel_outnames[] = { "out1", "out2", "led1", "led2", "led3", "led4", "out7", "out8", "out9", "out10", "out11" };

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
		case 9: self->set_main(ref); break;
		case 10: self->set_sw1(value); break;
		case 11: self->set_sw2(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_button_17; break;
		case 1: *value = self->m_ctrl_15; break;
		case 2: *value = self->m_ctrl_22; break;
		case 3: *value = self->m_ctrl_11; break;
		case 4: *value = self->m_ctrl_14; break;
		case 5: *value = self->m_ctrl_13; break;
		case 6: *value = self->m_ctrl_21; break;
		case 7: *value = self->m_ctrl_12; break;
		case 8: *value = self->m_gate_16; break;
		
		case 10: *value = self->m_sw_18; break;
		case 11: *value = self->m_sw_19; break;
		
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
	// initialize parameter 0 ("m_button_17")
	pi = self->__commonstate.params + 0;
	pi->name = "button";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_button_17;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_ctrl_15")
	pi = self->__commonstate.params + 1;
	pi->name = "ctrl1";
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
	// initialize parameter 2 ("m_ctrl_22")
	pi = self->__commonstate.params + 2;
	pi->name = "ctrl2";
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
	// initialize parameter 3 ("m_ctrl_11")
	pi = self->__commonstate.params + 3;
	pi->name = "ctrl3";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_11;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_ctrl_14")
	pi = self->__commonstate.params + 4;
	pi->name = "ctrl4";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_14;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_ctrl_13")
	pi = self->__commonstate.params + 5;
	pi->name = "ctrl5";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_13;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_ctrl_21")
	pi = self->__commonstate.params + 6;
	pi->name = "ctrl6";
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
	// initialize parameter 7 ("m_ctrl_12")
	pi = self->__commonstate.params + 7;
	pi->name = "ctrl7";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_12;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_gate_16")
	pi = self->__commonstate.params + 8;
	pi->name = "gate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_gate_16;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_main_20")
	pi = self->__commonstate.params + 9;
	pi->name = "main";
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
	// initialize parameter 10 ("m_sw_18")
	pi = self->__commonstate.params + 10;
	pi->name = "sw1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_18;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_sw_19")
	pi = self->__commonstate.params + 11;
	pi->name = "sw2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_19;
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


} // GiveTitle::
