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
	Data m_main_14;
	int __exception;
	int vectorsize;
	t_sample m_ctrl_16;
	t_sample m_ctrl_15;
	t_sample m_gate_17;
	t_sample m_button_18;
	t_sample m_ctrl_19;
	t_sample m_ctrl_20;
	t_sample __m_carry_24;
	t_sample m_sw_13;
	t_sample __m_count_22;
	t_sample m_ctrl_21;
	t_sample m_sw_12;
	t_sample m_ctrl_11;
	t_sample m_ctrl_10;
	t_sample m_history_2;
	t_sample m_history_3;
	t_sample m_history_1;
	t_sample samplerate;
	t_sample __m_count_28;
	t_sample m_history_4;
	t_sample m_history_6;
	t_sample m_history_9;
	t_sample m_history_5;
	t_sample m_history_8;
	t_sample m_history_7;
	t_sample __m_carry_30;
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
		m_ctrl_10 = ((int)0);
		m_ctrl_11 = ((int)0);
		m_sw_12 = ((int)0);
		m_sw_13 = ((int)0);
		m_main_14.reset("main", ((int)384000), ((int)2));
		m_ctrl_15 = ((int)0);
		m_ctrl_16 = ((int)0);
		m_gate_17 = ((int)0);
		m_button_18 = ((int)0);
		m_ctrl_19 = ((int)0);
		m_ctrl_20 = ((int)0);
		m_ctrl_21 = ((int)0);
		__m_count_22 = 0;
		__m_carry_24 = 0;
		__m_count_28 = 0;
		__m_carry_30 = 0;
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
		int main_dim = m_main_14.dim;
		int main_channels = m_main_14.channels;
		int main_dim_23630 = main_dim;
		int not_13882 = (!m_button_18);
		t_sample mstosamps_13884 = (((int)3000) * (samplerate * 0.001));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample out5 = ((int)0);
			t_sample out6 = ((int)0);
			t_sample out3 = ((int)0);
			t_sample out4 = ((int)0);
			__m_count_22 = (((int)0) ? 0 : (fixdenorm(__m_count_22 + ((int)1))));
			int carry_23 = 0;
			if ((((int)0) != 0)) {
				__m_count_22 = 0;
				__m_carry_24 = 0;
				
			} else if (((main_dim_23630 > 0) && (__m_count_22 >= main_dim_23630))) {
				int wraps_25 = (__m_count_22 / main_dim_23630);
				__m_carry_24 = (__m_carry_24 + wraps_25);
				__m_count_22 = (__m_count_22 - (wraps_25 * main_dim_23630));
				carry_23 = 1;
				
			};
			int counter_20842 = __m_count_22;
			int counter_20843 = carry_23;
			int counter_20844 = __m_carry_24;
			int index_wrap_26 = ((counter_20842 < 0) ? ((main_dim - 1) + ((counter_20842 + 1) % main_dim)) : (counter_20842 % main_dim));
			m_main_14.write(in1, index_wrap_26, 0);
			t_sample out11 = samplerate;
			t_sample out7 = ((int)0);
			t_sample out9 = ((int)0);
			int index_wrap_27 = ((counter_20842 < 0) ? ((main_dim - 1) + ((counter_20842 + 1) % main_dim)) : (counter_20842 % main_dim));
			// samples main channel 1;
			t_sample sample_main_23924 = m_main_14.read(index_wrap_27, 0);
			t_sample index_main_23925 = counter_20842;
			t_sample mul_23405 = (sample_main_23924 * ((int)1));
			t_sample mix_24332 = (m_history_9 + (((t_sample)0.0019634941468452) * (m_ctrl_16 - m_history_9)));
			t_sample mix_13923 = mix_24332;
			t_sample mix_24333 = (m_history_8 + (((t_sample)0.0019634941468452) * (mix_13923 - m_history_8)));
			t_sample mix_13921 = mix_24333;
			t_sample mix_24334 = (m_history_7 + (((t_sample)0.0019634941468452) * (mix_13921 - m_history_7)));
			t_sample mix_13919 = mix_24334;
			t_sample gen_13935 = mix_13919;
			t_sample history_13924_next_13926 = fixdenorm(mix_13923);
			t_sample history_13922_next_13927 = fixdenorm(mix_13921);
			t_sample history_13920_next_13928 = fixdenorm(mix_13919);
			t_sample mix_24335 = (mul_23405 + (gen_13935 * (((int)1) - mul_23405)));
			t_sample out1 = mix_24335;
			t_sample out2 = mix_24335;
			__m_count_28 = (not_13882 ? 0 : (fixdenorm(__m_count_28 + ((int)1))));
			int carry_29 = 0;
			if ((not_13882 != 0)) {
				__m_count_28 = 0;
				__m_carry_30 = 0;
				
			} else if (((mstosamps_13884 > 0) && (__m_count_28 >= mstosamps_13884))) {
				int wraps_31 = (__m_count_28 / mstosamps_13884);
				__m_carry_30 = (__m_carry_30 + wraps_31);
				__m_count_28 = (__m_count_28 - (wraps_31 * mstosamps_13884));
				carry_29 = 1;
				
			};
			int counter_13886 = __m_count_28;
			int counter_13887 = carry_29;
			int counter_13888 = __m_carry_30;
			t_sample out8 = counter_13887;
			t_sample mix_24336 = (m_history_6 + (((t_sample)0.0019634941468452) * (m_ctrl_10 - m_history_6)));
			t_sample mix_24295 = mix_24336;
			t_sample mix_24337 = (m_history_5 + (((t_sample)0.0019634941468452) * (mix_24295 - m_history_5)));
			t_sample mix_24288 = mix_24337;
			t_sample mix_24338 = (m_history_4 + (((t_sample)0.0019634941468452) * (mix_24288 - m_history_4)));
			t_sample mix_24291 = mix_24338;
			t_sample gen_13930 = mix_24291;
			t_sample history_13924_next_24289 = fixdenorm(mix_24295);
			t_sample history_13922_next_24294 = fixdenorm(mix_24288);
			t_sample history_13920_next_24292 = fixdenorm(mix_24291);
			t_sample mix_24339 = (m_history_3 + (((t_sample)0.0019634941468452) * (m_ctrl_19 - m_history_3)));
			t_sample mix_24308 = mix_24339;
			t_sample mix_24340 = (m_history_2 + (((t_sample)0.0019634941468452) * (mix_24308 - m_history_2)));
			t_sample mix_24301 = mix_24340;
			t_sample mix_24341 = (m_history_1 + (((t_sample)0.0019634941468452) * (mix_24301 - m_history_1)));
			t_sample mix_24305 = mix_24341;
			t_sample gen_13929 = mix_24305;
			t_sample history_13924_next_24302 = fixdenorm(mix_24308);
			t_sample history_13922_next_24303 = fixdenorm(mix_24301);
			t_sample history_13920_next_24306 = fixdenorm(mix_24305);
			t_sample add_13889 = (gen_13930 + gen_13929);
			int lt_13891 = (add_13889 < ((t_sample)0.001));
			int add_13878 = (counter_13888 + lt_13891);
			t_sample mod_13877 = safemod(add_13878, ((int)2));
			t_sample out10 = mod_13877;
			m_history_9 = history_13924_next_13926;
			m_history_7 = history_13920_next_13928;
			m_history_8 = history_13922_next_13927;
			m_history_6 = history_13924_next_24289;
			m_history_4 = history_13920_next_24292;
			m_history_5 = history_13922_next_24294;
			m_history_3 = history_13924_next_24302;
			m_history_1 = history_13920_next_24306;
			m_history_2 = history_13922_next_24303;
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
	inline void set_ctrl4(t_param _value) {
		m_ctrl_10 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl6(t_param _value) {
		m_ctrl_11 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_12 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw2(t_param _value) {
		m_sw_13 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_main(void * _value) {
		m_main_14.setbuffer(_value);
	};
	inline void set_ctrl5(t_param _value) {
		m_ctrl_15 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl1(t_param _value) {
		m_ctrl_16 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_gate(t_param _value) {
		m_gate_17 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_button(t_param _value) {
		m_button_18 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl7(t_param _value) {
		m_ctrl_19 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl3(t_param _value) {
		m_ctrl_20 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl2(t_param _value) {
		m_ctrl_21 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
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
		case 0: *value = self->m_button_18; break;
		case 1: *value = self->m_ctrl_16; break;
		case 2: *value = self->m_ctrl_21; break;
		case 3: *value = self->m_ctrl_20; break;
		case 4: *value = self->m_ctrl_10; break;
		case 5: *value = self->m_ctrl_15; break;
		case 6: *value = self->m_ctrl_11; break;
		case 7: *value = self->m_ctrl_19; break;
		case 8: *value = self->m_gate_17; break;
		
		case 10: *value = self->m_sw_12; break;
		case 11: *value = self->m_sw_13; break;
		
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
	// initialize parameter 0 ("m_button_18")
	pi = self->__commonstate.params + 0;
	pi->name = "button";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_button_18;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_ctrl_16")
	pi = self->__commonstate.params + 1;
	pi->name = "ctrl1";
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
	// initialize parameter 2 ("m_ctrl_21")
	pi = self->__commonstate.params + 2;
	pi->name = "ctrl2";
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
	// initialize parameter 3 ("m_ctrl_20")
	pi = self->__commonstate.params + 3;
	pi->name = "ctrl3";
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
	// initialize parameter 4 ("m_ctrl_10")
	pi = self->__commonstate.params + 4;
	pi->name = "ctrl4";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_10;
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
	// initialize parameter 6 ("m_ctrl_11")
	pi = self->__commonstate.params + 6;
	pi->name = "ctrl6";
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
	// initialize parameter 7 ("m_ctrl_19")
	pi = self->__commonstate.params + 7;
	pi->name = "ctrl7";
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
	// initialize parameter 8 ("m_gate_17")
	pi = self->__commonstate.params + 8;
	pi->name = "gate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_gate_17;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_main_14")
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
	// initialize parameter 10 ("m_sw_12")
	pi = self->__commonstate.params + 10;
	pi->name = "sw1";
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
	// initialize parameter 11 ("m_sw_13")
	pi = self->__commonstate.params + 11;
	pi->name = "sw2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_13;
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
