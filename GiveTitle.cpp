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
	int __exception;
	int vectorsize;
	t_sample m_sw_22;
	t_sample m_sw_23;
	t_sample m_ctrl_21;
	t_sample m_ctrl_20;
	t_sample m_history_19;
	t_sample m_ctrl_24;
	t_sample m_history_18;
	t_sample m_history_17;
	t_sample m_ctrl_25;
	t_sample m_ctrl_27;
	t_sample __m_count_31;
	t_sample __m_carry_33;
	t_sample m_ctrl_26;
	t_sample m_ctrl_30;
	t_sample m_gate_28;
	t_sample m_button_29;
	t_sample __m_slide_35;
	t_sample m_history_16;
	t_sample m_history_14;
	t_sample m_history_3;
	t_sample m_history_4;
	t_sample m_history_5;
	t_sample m_history_2;
	t_sample samplerate;
	t_sample m_history_1;
	t_sample m_history_15;
	t_sample m_history_6;
	t_sample m_d1R_8;
	t_sample m_history_12;
	t_sample m_history_13;
	t_sample m_d2R_7;
	t_sample m_history_11;
	t_sample m_d2L_9;
	t_sample m_d1L_10;
	t_sample __m_slide_38;
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
		m_d2R_7 = ((int)0);
		m_d1R_8 = ((int)0);
		m_d2L_9 = ((int)0);
		m_d1L_10 = ((int)0);
		m_history_11 = ((int)0);
		m_history_12 = ((int)0);
		m_history_13 = ((int)0);
		m_history_14 = ((int)0);
		m_history_15 = ((int)0);
		m_history_16 = ((int)0);
		m_history_17 = ((int)0);
		m_history_18 = ((int)0);
		m_history_19 = ((int)0);
		m_ctrl_20 = ((int)0);
		m_ctrl_21 = ((int)0);
		m_sw_22 = ((int)0);
		m_sw_23 = ((int)0);
		m_ctrl_24 = ((int)0);
		m_ctrl_25 = ((int)0);
		m_ctrl_26 = ((int)0);
		m_ctrl_27 = ((int)0);
		m_gate_28 = ((int)0);
		m_button_29 = ((int)0);
		m_ctrl_30 = ((int)0);
		__m_count_31 = 0;
		__m_carry_33 = 0;
		__m_slide_35 = 0;
		__m_slide_38 = 0;
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
		int not_11797 = (!m_button_29);
		t_sample mstosamps_10261 = (((int)3000) * (samplerate * 0.001));
		t_sample iup_36 = (1 / maximum(1, abs(((int)4000))));
		t_sample idown_37 = (1 / maximum(1, abs(((int)4000))));
		t_sample iup_39 = (1 / maximum(1, abs(((int)4000))));
		t_sample idown_40 = (1 / maximum(1, abs(((int)4000))));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample out5 = ((int)0);
			t_sample out3 = ((int)0);
			t_sample out4 = ((int)0);
			t_sample out6 = ((int)0);
			t_sample out9 = ((int)0);
			t_sample expr_20457 = (in1 + in2);
			t_sample expr_20458 = (in1 - in2);
			t_sample out11 = samplerate;
			t_sample out7 = ((int)0);
			__m_count_31 = (not_11797 ? 0 : (fixdenorm(__m_count_31 + ((int)1))));
			int carry_32 = 0;
			if ((not_11797 != 0)) {
				__m_count_31 = 0;
				__m_carry_33 = 0;
				
			} else if (((mstosamps_10261 > 0) && (__m_count_31 >= mstosamps_10261))) {
				int wraps_34 = (__m_count_31 / mstosamps_10261);
				__m_carry_33 = (__m_carry_33 + wraps_34);
				__m_count_31 = (__m_count_31 - (wraps_34 * mstosamps_10261));
				carry_32 = 1;
				
			};
			int counter_9903 = __m_count_31;
			int counter_9904 = carry_32;
			int counter_9905 = __m_carry_33;
			t_sample out8 = counter_9904;
			t_sample mix_20594 = (m_history_19 + (((t_sample)0.0019634941468452) * (m_ctrl_27 - m_history_19)));
			t_sample mix_88 = mix_20594;
			t_sample mix_20595 = (m_history_18 + (((t_sample)0.0019634941468452) * (mix_88 - m_history_18)));
			t_sample mix_86 = mix_20595;
			t_sample mix_20596 = (m_history_17 + (((t_sample)0.0019634941468452) * (mix_86 - m_history_17)));
			t_sample mix_84 = mix_20596;
			t_sample gen_100 = mix_84;
			t_sample history_89_next_91 = fixdenorm(mix_88);
			t_sample history_87_next_92 = fixdenorm(mix_86);
			t_sample history_85_next_93 = fixdenorm(mix_84);
			t_sample sub_20600 = (gen_100 - ((int)0));
			t_sample scale_20597 = ((safepow((sub_20600 * ((t_sample)1)), ((int)1)) * ((int)3)) + ((int)1));
			t_sample mix_20601 = (m_history_16 + (((t_sample)0.0019634941468452) * (m_ctrl_25 - m_history_16)));
			t_sample mix_20464 = mix_20601;
			t_sample mix_20602 = (m_history_15 + (((t_sample)0.0019634941468452) * (mix_20464 - m_history_15)));
			t_sample mix_20468 = mix_20602;
			t_sample mix_20603 = (m_history_14 + (((t_sample)0.0019634941468452) * (mix_20468 - m_history_14)));
			t_sample mix_20461 = mix_20603;
			t_sample gen_98 = mix_20461;
			t_sample history_89_next_20469 = fixdenorm(mix_20464);
			t_sample history_87_next_20467 = fixdenorm(mix_20468);
			t_sample history_85_next_20463 = fixdenorm(mix_20461);
			t_sample TONE_242 = gen_98;
			t_sample sub_20607 = (TONE_242 - ((int)0));
			t_sample scale_20604 = ((safepow((sub_20607 * ((t_sample)1)), ((int)1)) * ((int)11999)) + ((int)1));
			t_sample scale_3471 = scale_20604;
			__m_slide_35 = fixdenorm((__m_slide_35 + (((scale_3471 > __m_slide_35) ? iup_36 : idown_37) * (scale_3471 - __m_slide_35))));
			t_sample slide_1693 = __m_slide_35;
			t_sample mix_20608 = (m_history_13 + (((t_sample)0.0019634941468452) * (m_ctrl_30 - m_history_13)));
			t_sample mix_20477 = mix_20608;
			t_sample mix_20609 = (m_history_12 + (((t_sample)0.0019634941468452) * (mix_20477 - m_history_12)));
			t_sample mix_20481 = mix_20609;
			t_sample mix_20610 = (m_history_11 + (((t_sample)0.0019634941468452) * (mix_20481 - m_history_11)));
			t_sample mix_20474 = mix_20610;
			t_sample gen_99 = mix_20474;
			t_sample history_89_next_20482 = fixdenorm(mix_20477);
			t_sample history_87_next_20480 = fixdenorm(mix_20481);
			t_sample history_85_next_20476 = fixdenorm(mix_20474);
			t_sample REGEN_274 = gen_99;
			t_sample sub_20614 = (REGEN_274 - ((int)0));
			t_sample scale_20611 = ((safepow((sub_20614 * ((t_sample)1)), ((int)1)) * ((t_sample)99.5)) + ((t_sample)0.5));
			t_sample scale_348 = scale_20611;
			__m_slide_38 = fixdenorm((__m_slide_38 + (((scale_348 > __m_slide_38) ? iup_39 : idown_40) * (scale_348 - __m_slide_38))));
			t_sample slide_1743 = __m_slide_38;
			t_sample q1 = safediv(((int)1), slide_1743);
			t_sample f1 = fastersinfull(safediv((((t_sample)6.2831853071796) * slide_1693), samplerate));
			t_sample LL = (m_d2L_9 + (f1 * m_d1L_10));
			t_sample HL = ((expr_20457 - LL) - (q1 * m_d1L_10));
			t_sample BL = ((f1 * HL) + m_d1L_10);
			t_sample NL = (HL + LL);
			t_sample LR = (m_d2R_7 + (f1 * m_d1R_8));
			t_sample HR = ((expr_20458 - LR) - (q1 * m_d1R_8));
			t_sample BR = ((f1 * HR) + m_d1R_8);
			t_sample NR = (HR + LR);
			m_d1L_10 = BL;
			m_d2L_9 = LL;
			m_d1R_8 = BR;
			m_d2R_7 = LR;
			t_sample choice_41 = int(scale_20597);
			t_sample selector_1863 = ((choice_41 >= 4) ? HL : ((choice_41 >= 3) ? NL : ((choice_41 >= 2) ? BL : ((choice_41 >= 1) ? LL : 0))));
			t_sample choice_42 = int(scale_20597);
			t_sample selector_1885 = ((choice_42 >= 4) ? LR : ((choice_42 >= 3) ? BR : ((choice_42 >= 2) ? NR : ((choice_42 >= 1) ? HR : 0))));
			t_sample expr_20459 = ((selector_1863 + selector_1885) * ((t_sample)0.5));
			t_sample expr_20460 = ((selector_1863 - selector_1885) * ((t_sample)0.5));
			t_sample mix_20615 = (m_history_6 + (((t_sample)0.0019634941468452) * (m_ctrl_20 - m_history_6)));
			t_sample mix_20492 = mix_20615;
			t_sample mix_20616 = (m_history_5 + (((t_sample)0.0019634941468452) * (mix_20492 - m_history_5)));
			t_sample mix_20495 = mix_20616;
			t_sample mix_20617 = (m_history_4 + (((t_sample)0.0019634941468452) * (mix_20495 - m_history_4)));
			t_sample mix_20490 = mix_20617;
			t_sample gen_95 = mix_20490;
			t_sample history_89_next_20489 = fixdenorm(mix_20492);
			t_sample history_87_next_20494 = fixdenorm(mix_20495);
			t_sample history_85_next_20487 = fixdenorm(mix_20490);
			t_sample mix_20618 = (m_history_3 + (((t_sample)0.0019634941468452) * (m_ctrl_21 - m_history_3)));
			t_sample mix_20505 = mix_20618;
			t_sample mix_20619 = (m_history_2 + (((t_sample)0.0019634941468452) * (mix_20505 - m_history_2)));
			t_sample mix_20508 = mix_20619;
			t_sample mix_20620 = (m_history_1 + (((t_sample)0.0019634941468452) * (mix_20508 - m_history_1)));
			t_sample mix_20503 = mix_20620;
			t_sample gen_94 = mix_20503;
			t_sample history_89_next_20502 = fixdenorm(mix_20505);
			t_sample history_87_next_20507 = fixdenorm(mix_20508);
			t_sample history_85_next_20500 = fixdenorm(mix_20503);
			t_sample add_9232 = (gen_95 + gen_94);
			int lt_8634 = (add_9232 < ((t_sample)0.001));
			int add_15227 = (counter_9905 + lt_8634);
			t_sample mod_19620 = safemod(add_15227, ((int)2));
			t_sample out10 = mod_19620;
			int eq_20448 = (mod_19620 == ((int)0));
			t_sample switch_14754 = (eq_20448 ? in2 : expr_20460);
			t_sample out2 = switch_14754;
			t_sample switch_14162 = (eq_20448 ? in1 : expr_20459);
			t_sample out1 = switch_14162;
			m_history_19 = history_89_next_91;
			m_history_17 = history_85_next_93;
			m_history_18 = history_87_next_92;
			m_history_16 = history_89_next_20469;
			m_history_14 = history_85_next_20463;
			m_history_15 = history_87_next_20467;
			m_history_13 = history_89_next_20482;
			m_history_11 = history_85_next_20476;
			m_history_12 = history_87_next_20480;
			m_history_6 = history_89_next_20489;
			m_history_4 = history_85_next_20487;
			m_history_5 = history_87_next_20494;
			m_history_3 = history_89_next_20502;
			m_history_1 = history_85_next_20500;
			m_history_2 = history_87_next_20507;
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
		m_ctrl_20 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl7(t_param _value) {
		m_ctrl_21 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw2(t_param _value) {
		m_sw_22 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_23 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl2(t_param _value) {
		m_ctrl_24 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl3(t_param _value) {
		m_ctrl_25 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl6(t_param _value) {
		m_ctrl_26 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl1(t_param _value) {
		m_ctrl_27 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_gate(t_param _value) {
		m_gate_28 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_button(t_param _value) {
		m_button_29 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl5(t_param _value) {
		m_ctrl_30 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
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
int num_params() { return 11; }

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
		case 9: self->set_sw1(value); break;
		case 10: self->set_sw2(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_button_29; break;
		case 1: *value = self->m_ctrl_27; break;
		case 2: *value = self->m_ctrl_24; break;
		case 3: *value = self->m_ctrl_25; break;
		case 4: *value = self->m_ctrl_20; break;
		case 5: *value = self->m_ctrl_30; break;
		case 6: *value = self->m_ctrl_26; break;
		case 7: *value = self->m_ctrl_21; break;
		case 8: *value = self->m_gate_28; break;
		case 9: *value = self->m_sw_23; break;
		case 10: *value = self->m_sw_22; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(11 * sizeof(ParamInfo));
	self->__commonstate.numparams = 11;
	// initialize parameter 0 ("m_button_29")
	pi = self->__commonstate.params + 0;
	pi->name = "button";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_button_29;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_ctrl_27")
	pi = self->__commonstate.params + 1;
	pi->name = "ctrl1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_27;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_ctrl_24")
	pi = self->__commonstate.params + 2;
	pi->name = "ctrl2";
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
	// initialize parameter 3 ("m_ctrl_25")
	pi = self->__commonstate.params + 3;
	pi->name = "ctrl3";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_25;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_ctrl_20")
	pi = self->__commonstate.params + 4;
	pi->name = "ctrl4";
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
	// initialize parameter 5 ("m_ctrl_30")
	pi = self->__commonstate.params + 5;
	pi->name = "ctrl5";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_30;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_ctrl_26")
	pi = self->__commonstate.params + 6;
	pi->name = "ctrl6";
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
	// initialize parameter 7 ("m_ctrl_21")
	pi = self->__commonstate.params + 7;
	pi->name = "ctrl7";
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
	// initialize parameter 8 ("m_gate_28")
	pi = self->__commonstate.params + 8;
	pi->name = "gate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_gate_28;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_sw_23")
	pi = self->__commonstate.params + 9;
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
	// initialize parameter 10 ("m_sw_22")
	pi = self->__commonstate.params + 10;
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
