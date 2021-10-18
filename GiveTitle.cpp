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
	Data m_stutter_20;
	Data m_main_23;
	Delta __m_delta_48;
	PlusEquals __m_pluseq_49;
	Rate __m_rate_38;
	int __exception;
	int vectorsize;
	t_sample m_ctrl_24;
	t_sample m_button_25;
	t_sample m_gate_21;
	t_sample m_sw_22;
	t_sample m_ctrl_26;
	t_sample __m_carry_29;
	t_sample m_ctrl_19;
	t_sample __m_latch_51;
	t_sample __m_count_27;
	t_sample __m_count_50;
	t_sample __m_count_33;
	t_sample __m_carry_35;
	t_sample m_ctrl_18;
	t_sample m_sw_17;
	t_sample m_ctrl_16;
	t_sample m_history_4;
	t_sample m_history_5;
	t_sample m_history_6;
	t_sample m_history_3;
	t_sample m_history_1;
	t_sample m_history_2;
	t_sample samplerate;
	t_sample __m_count_52;
	t_sample m_history_7;
	t_sample m_history_9;
	t_sample m_ctrl_14;
	t_sample m_ctrl_15;
	t_sample m_history_8;
	t_sample m_history_13;
	t_sample m_history_11;
	t_sample m_history_12;
	t_sample m_history_10;
	t_sample __m_carry_54;
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
		m_history_12 = ((int)0);
		m_history_13 = ((int)0);
		m_ctrl_14 = ((int)0);
		m_ctrl_15 = ((int)0);
		m_ctrl_16 = ((int)0);
		m_sw_17 = ((int)0);
		m_ctrl_18 = ((int)0);
		m_ctrl_19 = ((int)0);
		m_stutter_20.reset("stutter", ((int)384000), ((int)2));
		m_gate_21 = ((int)0);
		m_sw_22 = ((int)0);
		m_main_23.reset("main", ((int)384000), ((int)2));
		m_ctrl_24 = ((int)0);
		m_button_25 = ((int)0);
		m_ctrl_26 = ((int)0);
		__m_count_27 = 0;
		__m_carry_29 = 0;
		__m_count_33 = 0;
		__m_carry_35 = 0;
		__m_rate_38.reset();
		__m_delta_48.reset(0);
		__m_pluseq_49.reset(0);
		__m_count_50 = 0;
		__m_latch_51 = 0;
		__m_count_52 = 0;
		__m_carry_54 = 0;
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
		int main_dim = m_main_23.dim;
		int main_channels = m_main_23.channels;
		int main_dim_20 = main_dim;
		int dim_1667 = main_dim;
		int stutter_dim = m_stutter_20.dim;
		int stutter_channels = m_stutter_20.channels;
		int irange_10008 = (dim_1667 - ((int)1));
		int or_97 = (m_gate_21 || m_button_25);
		int not_25 = (!m_button_25);
		t_sample mstosamps_27 = (((int)3000) * (samplerate * 0.001));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample out3 = ((int)0);
			t_sample out4 = ((int)0);
			t_sample out5 = ((int)0);
			t_sample out6 = ((int)0);
			t_sample out11 = samplerate;
			__m_count_27 = (((int)0) ? 0 : (fixdenorm(__m_count_27 + ((int)1))));
			int carry_28 = 0;
			if ((((int)0) != 0)) {
				__m_count_27 = 0;
				__m_carry_29 = 0;
				
			} else if (((main_dim_20 > 0) && (__m_count_27 >= main_dim_20))) {
				int wraps_30 = (__m_count_27 / main_dim_20);
				__m_carry_29 = (__m_carry_29 + wraps_30);
				__m_count_27 = (__m_count_27 - (wraps_30 * main_dim_20));
				carry_28 = 1;
				
			};
			int counter_13 = __m_count_27;
			int counter_14 = carry_28;
			int counter_15 = __m_carry_29;
			int index_wrap_31 = ((counter_13 < 0) ? ((main_dim - 1) + ((counter_13 + 1) % main_dim)) : (counter_13 % main_dim));
			m_main_23.write(in1, index_wrap_31, 0);
			int index_wrap_32 = ((counter_13 < 0) ? ((main_dim - 1) + ((counter_13 + 1) % main_dim)) : (counter_13 % main_dim));
			// samples main channel 1;
			t_sample sample_main_16 = m_main_23.read(index_wrap_32, 0);
			t_sample index_main_17 = counter_13;
			t_sample mix_9997 = (m_history_13 + (((t_sample)0.0042742627044161) * (m_ctrl_24 - m_history_13)));
			t_sample mix_56 = mix_9997;
			t_sample mix_9998 = (m_history_12 + (((t_sample)0.0042742627044161) * (mix_56 - m_history_12)));
			t_sample mix_54 = mix_9998;
			t_sample mix_9999 = (m_history_11 + (((t_sample)0.0042742627044161) * (mix_54 - m_history_11)));
			t_sample mix_52 = mix_9999;
			t_sample gen_77 = mix_52;
			t_sample history_57_next_63 = fixdenorm(mix_56);
			t_sample history_55_next_64 = fixdenorm(mix_54);
			t_sample history_53_next_65 = fixdenorm(mix_52);
			t_sample mix_10000 = (m_history_10 + (((t_sample)0.0042742627044161) * (m_ctrl_14 - m_history_10)));
			t_sample mix_9900 = mix_10000;
			t_sample mix_10001 = (m_history_9 + (((t_sample)0.0042742627044161) * (mix_9900 - m_history_9)));
			t_sample mix_9892 = mix_10001;
			t_sample mix_10002 = (m_history_8 + (((t_sample)0.0042742627044161) * (mix_9892 - m_history_8)));
			t_sample mix_9896 = mix_10002;
			t_sample gen_75 = mix_9896;
			t_sample history_57_next_9893 = fixdenorm(mix_9900);
			t_sample history_55_next_9894 = fixdenorm(mix_9892);
			t_sample history_53_next_9898 = fixdenorm(mix_9896);
			t_sample sub_10006 = (gen_75 - ((int)0));
			t_sample scale_10003 = ((safepow((sub_10006 * ((t_sample)1)), ((int)1)) * ((int)383999)) + ((int)1));
			__m_count_33 = (((int)0) ? 0 : (fixdenorm(__m_count_33 + ((int)1))));
			int carry_34 = 0;
			if ((((int)0) != 0)) {
				__m_count_33 = 0;
				__m_carry_35 = 0;
				
			} else if (((scale_10003 > 0) && (__m_count_33 >= scale_10003))) {
				int wraps_36 = (__m_count_33 / scale_10003);
				__m_carry_35 = (__m_carry_35 + wraps_36);
				__m_count_33 = (__m_count_33 - (wraps_36 * scale_10003));
				carry_34 = 1;
				
			};
			int counter_5317 = __m_count_33;
			int counter_5318 = carry_34;
			int counter_5319 = __m_carry_35;
			int index_clamp_37 = ((counter_5317 < 0) ? 0 : ((counter_5317 > stutter_dim) ? stutter_dim : counter_5317));
			m_stutter_20.write(sample_main_16, index_clamp_37, 0);
			int sub_10010 = (counter_5317 - ((int)1));
			t_sample scale_10007 = ((safepow(safediv(sub_10010, irange_10008), ((int)1)) * ((int)1)) + ((int)0));
			t_sample rate_659 = __m_rate_38.perform_off(scale_10007, ((int)1));
			t_sample out7 = rate_659;
			t_sample out9 = rate_659;
			double sample_index_39 = (rate_659 * (stutter_dim - 1));
			int index_trunc_40 = fixnan(floor(sample_index_39));
			double index_fract_41 = (sample_index_39 - index_trunc_40);
			int index_trunc_42 = (index_trunc_40 + 1);
			int index_clamp_43 = ((index_trunc_40 < 0) ? 0 : ((index_trunc_40 > stutter_dim) ? stutter_dim : index_trunc_40));
			int index_clamp_44 = ((index_trunc_42 < 0) ? 0 : ((index_trunc_42 > stutter_dim) ? stutter_dim : index_trunc_42));
			// phase stutter channel 1;
			double read_stutter_45 = m_stutter_20.read(index_clamp_43, 0);
			double read_stutter_46 = m_stutter_20.read(index_clamp_44, 0);
			double readinterp_47 = linear_interp(index_fract_41, read_stutter_45, read_stutter_46);
			t_sample sample_stutter_9890 = readinterp_47;
			t_sample index_stutter_9891 = sample_index_39;
			t_sample mix_10011 = (sample_main_16 + (gen_77 * (sample_stutter_9890 - sample_main_16)));
			t_sample out1 = mix_10011;
			t_sample out2 = mix_10011;
			int delta_90 = __m_delta_48(or_97);
			int gtep_89 = ((delta_90 >= ((int)1)) ? delta_90 : 0);
			t_sample plusequals_88 = __m_pluseq_49.post(gtep_89, m_history_7, 0);
			int eq_86 = (plusequals_88 == ((int)2));
			__m_count_50 = (m_history_7 ? 0 : (fixdenorm(__m_count_50 + plusequals_88)));
			t_sample counter_83 = __m_count_50;
			int counter_84 = ((int)0);
			int counter_85 = ((int)0);
			__m_latch_51 = ((eq_86 != 0) ? counter_83 : __m_latch_51);
			t_sample latch_82 = __m_latch_51;
			t_sample history_87_next_94 = fixdenorm(eq_86);
			t_sample div_7250 = safediv(latch_82, samplerate);
			t_sample out10 = div_7250;
			__m_count_52 = (not_25 ? 0 : (fixdenorm(__m_count_52 + ((int)1))));
			int carry_53 = 0;
			if ((not_25 != 0)) {
				__m_count_52 = 0;
				__m_carry_54 = 0;
				
			} else if (((mstosamps_27 > 0) && (__m_count_52 >= mstosamps_27))) {
				int wraps_55 = (__m_count_52 / mstosamps_27);
				__m_carry_54 = (__m_carry_54 + wraps_55);
				__m_count_52 = (__m_count_52 - (wraps_55 * mstosamps_27));
				carry_53 = 1;
				
			};
			int counter_29 = __m_count_52;
			int counter_30 = carry_53;
			int counter_31 = __m_carry_54;
			t_sample mix_10012 = (m_history_6 + (((t_sample)0.0042742627044161) * (m_ctrl_15 - m_history_6)));
			t_sample mix_9906 = mix_10012;
			t_sample mix_10013 = (m_history_5 + (((t_sample)0.0042742627044161) * (mix_9906 - m_history_5)));
			t_sample mix_9907 = mix_10013;
			t_sample mix_10014 = (m_history_4 + (((t_sample)0.0042742627044161) * (mix_9907 - m_history_4)));
			t_sample mix_9908 = mix_10014;
			t_sample gen_67 = mix_9908;
			t_sample history_57_next_9910 = fixdenorm(mix_9906);
			t_sample history_55_next_9911 = fixdenorm(mix_9907);
			t_sample history_53_next_9905 = fixdenorm(mix_9908);
			t_sample mix_10015 = (m_history_3 + (((t_sample)0.0042742627044161) * (m_ctrl_18 - m_history_3)));
			t_sample mix_9919 = mix_10015;
			t_sample mix_10016 = (m_history_2 + (((t_sample)0.0042742627044161) * (mix_9919 - m_history_2)));
			t_sample mix_9920 = mix_10016;
			t_sample mix_10017 = (m_history_1 + (((t_sample)0.0042742627044161) * (mix_9920 - m_history_1)));
			t_sample mix_9921 = mix_10017;
			t_sample gen_113 = mix_9921;
			t_sample history_57_next_9923 = fixdenorm(mix_9919);
			t_sample history_55_next_9924 = fixdenorm(mix_9920);
			t_sample history_53_next_9918 = fixdenorm(mix_9921);
			t_sample add_32 = (gen_67 + gen_113);
			int lt_34 = (add_32 < ((t_sample)0.001));
			int add_23 = (counter_31 + lt_34);
			t_sample mod_22 = safemod(add_23, ((int)2));
			t_sample out8 = mod_22;
			m_history_13 = history_57_next_63;
			m_history_11 = history_53_next_65;
			m_history_12 = history_55_next_64;
			m_history_10 = history_57_next_9893;
			m_history_8 = history_53_next_9898;
			m_history_9 = history_55_next_9894;
			m_history_7 = history_87_next_94;
			m_history_6 = history_57_next_9910;
			m_history_4 = history_53_next_9905;
			m_history_5 = history_55_next_9911;
			m_history_3 = history_57_next_9923;
			m_history_1 = history_53_next_9918;
			m_history_2 = history_55_next_9924;
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
	inline void set_ctrl5(t_param _value) {
		m_ctrl_14 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl4(t_param _value) {
		m_ctrl_15 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl2(t_param _value) {
		m_ctrl_16 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_17 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl7(t_param _value) {
		m_ctrl_18 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl6(t_param _value) {
		m_ctrl_19 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_stutter(void * _value) {
		m_stutter_20.setbuffer(_value);
	};
	inline void set_gate(t_param _value) {
		m_gate_21 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw2(t_param _value) {
		m_sw_22 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_main(void * _value) {
		m_main_23.setbuffer(_value);
	};
	inline void set_ctrl1(t_param _value) {
		m_ctrl_24 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_button(t_param _value) {
		m_button_25 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl3(t_param _value) {
		m_ctrl_26 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
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
int num_params() { return 13; }

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
		case 10: self->set_stutter(ref); break;
		case 11: self->set_sw1(value); break;
		case 12: self->set_sw2(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_button_25; break;
		case 1: *value = self->m_ctrl_24; break;
		case 2: *value = self->m_ctrl_16; break;
		case 3: *value = self->m_ctrl_26; break;
		case 4: *value = self->m_ctrl_15; break;
		case 5: *value = self->m_ctrl_14; break;
		case 6: *value = self->m_ctrl_19; break;
		case 7: *value = self->m_ctrl_18; break;
		case 8: *value = self->m_gate_21; break;
		
		
		case 11: *value = self->m_sw_17; break;
		case 12: *value = self->m_sw_22; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(13 * sizeof(ParamInfo));
	self->__commonstate.numparams = 13;
	// initialize parameter 0 ("m_button_25")
	pi = self->__commonstate.params + 0;
	pi->name = "button";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_button_25;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_ctrl_24")
	pi = self->__commonstate.params + 1;
	pi->name = "ctrl1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_24;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_ctrl_16")
	pi = self->__commonstate.params + 2;
	pi->name = "ctrl2";
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
	// initialize parameter 3 ("m_ctrl_26")
	pi = self->__commonstate.params + 3;
	pi->name = "ctrl3";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_26;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_ctrl_15")
	pi = self->__commonstate.params + 4;
	pi->name = "ctrl4";
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
	// initialize parameter 5 ("m_ctrl_14")
	pi = self->__commonstate.params + 5;
	pi->name = "ctrl5";
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
	// initialize parameter 6 ("m_ctrl_19")
	pi = self->__commonstate.params + 6;
	pi->name = "ctrl6";
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
	// initialize parameter 7 ("m_ctrl_18")
	pi = self->__commonstate.params + 7;
	pi->name = "ctrl7";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_18;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_gate_21")
	pi = self->__commonstate.params + 8;
	pi->name = "gate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_gate_21;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_main_23")
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
	// initialize parameter 10 ("m_stutter_20")
	pi = self->__commonstate.params + 10;
	pi->name = "stutter";
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
	// initialize parameter 11 ("m_sw_17")
	pi = self->__commonstate.params + 11;
	pi->name = "sw1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_17;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_sw_22")
	pi = self->__commonstate.params + 12;
	pi->name = "sw2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_22;
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
