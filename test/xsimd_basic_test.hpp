/***************************************************************************
* Copyright (c) 2016, Johan Mabille and Sylvain Corlay                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XSIMD_BASIC_TEST_HPP
#define XSIMD_BASIC_TEST_HPP

#include "xsimd_tester.hpp"
#include "xsimd_test_utils.hpp"

namespace xsimd
{

    /****************
     * basic tester *
     ****************/

    template <class T, std::size_t N, std::size_t A>
    struct simd_basic_tester : simd_tester<T, N, A>
    {
        using base_type = simd_tester<T, N, A>;
        using vector_type = typename base_type::vector_type;
        using value_type = typename base_type::value_type;
        using res_type = typename base_type::res_type;

        std::string name;

        value_type s;
        res_type lhs;
        res_type rhs;

        value_type extract_res;
        res_type minus_res;
        res_type add_vv_res;
        res_type add_vs_res;
        res_type add_sv_res;
        res_type sub_vv_res;
        res_type sub_vs_res;
        res_type sub_sv_res;
        res_type mul_vv_res;
        res_type mul_vs_res;
        res_type mul_sv_res;
        res_type div_vv_res;
        res_type div_vs_res;
        res_type div_sv_res;
        res_type and_res;
        res_type or_res;
        res_type xor_res;
        res_type not_res;
        res_type lnot_res;
        res_type min_res;
        res_type max_res;
        res_type abs_res;
        res_type fma_res;
        res_type fms_res;
        res_type fnma_res;
        res_type fnms_res;
        res_type sqrt_res;
        value_type hadd_res;
        
        simd_basic_tester(const std::string& name);
    };


    template <class T, size_t N, size_t A>
    simd_basic_tester<T, N, A>::simd_basic_tester(const std::string& n)
        : name(n)
    {
        using std::min;
        using std::max;
        using std::abs;
        using std::sqrt;
        using std::fma;

        lhs.resize(N);
        rhs.resize(N);
        minus_res.resize(N);
        add_vv_res.resize(N);
        add_vs_res.resize(N);
        add_sv_res.resize(N);
        sub_vv_res.resize(N);
        sub_vs_res.resize(N);
        sub_sv_res.resize(N);
        mul_vv_res.resize(N);
        mul_vs_res.resize(N);
        mul_sv_res.resize(N);
        div_vv_res.resize(N);
        div_vs_res.resize(N);
        div_sv_res.resize(N);
        and_res.resize(N);
        or_res.resize(N);
        xor_res.resize(N);
        not_res.resize(N);
        lnot_res.resize(N);
        min_res.resize(N);
        max_res.resize(N);
        abs_res.resize(N);
        fma_res.resize(N);
        fms_res.resize(N);
        fnma_res.resize(N);
        fnms_res.resize(N);
        sqrt_res.resize(N);

        s = value_type(1.4);
        hadd_res = value_type(0);
        for(size_t i = 0; i < N; ++i)
        {
            lhs[i] = value_type(i) / 4 + value_type(1.2) * std::sqrt(value_type(i + 0.25));
            rhs[i] = value_type(10.2) / (i+2) + value_type(0.25);
            extract_res = lhs[1];
            minus_res[i] = -lhs[i];
            add_vv_res[i] = lhs[i] + rhs[i];
            add_vs_res[i] = lhs[i] + s;
            add_sv_res[i] = s + rhs[i];
            sub_vv_res[i] = lhs[i] - rhs[i];
            sub_vs_res[i] = lhs[i] - s;
            sub_sv_res[i] = s - rhs[i];
            mul_vv_res[i] = lhs[i] * rhs[i];
            mul_vs_res[i] = lhs[i] * s;
            mul_sv_res[i] = s * rhs[i];
            div_vv_res[i] = lhs[i] / rhs[i];
            div_vs_res[i] = lhs[i] / s;
            div_sv_res[i] = s / rhs[i];
            //and_res[i] = lhs[i] & rhs[i];
            //or_res[i] = lhs[i] | rhs[i];
            //xor_res[i] = lhs[i] ^ rhs[i];
            //not_res[i] = ~lhs[i];
            //lnot_res[i] = !lhs[i];
            min_res[i] = min(lhs[i], rhs[i]);
            max_res[i] = max(lhs[i], rhs[i]);
            abs_res[i] = abs(lhs[i]);
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_FMA4_VERSION
            fma_res[i] = fma(lhs[i], rhs[i], rhs[i]);
#else
            fma_res[i] = lhs[i] * rhs[i] + rhs[i];
#endif
            fms_res[i] = lhs[i] * rhs[i] - rhs[i];
            fnma_res[i] = - lhs[i] * rhs[i] + rhs[i];
            fnms_res[i] = - lhs[i] * rhs[i] - rhs[i];
            sqrt_res[i] = sqrt(lhs[i]);
            hadd_res += lhs[i];
        }
    }

    template <class T, std::size_t N, std::size_t A>
    struct simd_int_basic_tester : simd_tester<T, N, A>
    {
        using base_type = simd_tester<T, N, A>;
        using vector_type = typename base_type::vector_type;
        using value_type = typename base_type::value_type;
        using res_type = typename base_type::res_type;

        std::string name;

        value_type s;
        int32_t sh_nb;
        res_type lhs;
        res_type rhs;

        value_type extract_res;
        res_type minus_res;
        res_type add_vv_res;
        res_type add_vs_res;
        res_type add_sv_res;
        res_type sub_vv_res;
        res_type sub_vs_res;
        res_type sub_sv_res;
        res_type mul_vv_res;
        res_type mul_vs_res;
        res_type mul_sv_res;
        res_type and_res;
        res_type or_res;
        res_type xor_res;
        res_type not_res;
        res_type lnot_res;
        res_type min_res;
        res_type max_res;
        res_type abs_res;
        res_type fma_res;
        res_type fms_res;
        res_type fnma_res;
        res_type fnms_res;
        value_type hadd_res;
        res_type sl_res;
        res_type sr_res;

        simd_int_basic_tester(const std::string& name);
    };


    template <class T, size_t N, size_t A>
    simd_int_basic_tester<T, N, A>::simd_int_basic_tester(const std::string& n)
        : name(n)
    {
        using std::min;
        using std::max;
        using std::abs;

        lhs.resize(N);
        rhs.resize(N);
        minus_res.resize(N);
        add_vv_res.resize(N);
        add_vs_res.resize(N);
        add_sv_res.resize(N);
        sub_vv_res.resize(N);
        sub_vs_res.resize(N);
        sub_sv_res.resize(N);
        mul_vv_res.resize(N);
        mul_vs_res.resize(N);
        mul_sv_res.resize(N);
        and_res.resize(N);
        or_res.resize(N);
        xor_res.resize(N);
        not_res.resize(N);
        lnot_res.resize(N);
        min_res.resize(N);
        max_res.resize(N);
        abs_res.resize(N);
        fma_res.resize(N);
        fms_res.resize(N);
        fnma_res.resize(N);
        fnms_res.resize(N);
        sl_res.resize(N);
        sr_res.resize(N);

        s = value_type(1.4);
        sh_nb = 3;
        hadd_res = value_type(0);
        for (size_t i = 0; i < N; ++i)
        {
            lhs[i] = value_type(i) * 10;
            rhs[i] = value_type(4) + value_type(i);
            extract_res = lhs[1];
            minus_res[i] = -lhs[i];
            add_vv_res[i] = lhs[i] + rhs[i];
            add_vs_res[i] = lhs[i] + s;
            add_sv_res[i] = s + rhs[i];
            sub_vv_res[i] = lhs[i] - rhs[i];
            sub_vs_res[i] = lhs[i] - s;
            sub_sv_res[i] = s - rhs[i];
            mul_vv_res[i] = lhs[i] * rhs[i];
            mul_vs_res[i] = lhs[i] * s;
            mul_sv_res[i] = s * rhs[i];
            //and_res[i] = lhs[i] & rhs[i];
            //or_res[i] = lhs[i] | rhs[i];
            //xor_res[i] = lhs[i] ^ rhs[i];
            //not_res[i] = ~lhs[i];
            //lnot_res[i] = !lhs[i];
            min_res[i] = min(lhs[i], rhs[i]);
            max_res[i] = max(lhs[i], rhs[i]);
            abs_res[i] = abs(lhs[i]);
            fma_res[i] = lhs[i] * rhs[i] + rhs[i];
            fms_res[i] = lhs[i] * rhs[i] - rhs[i];
            fnma_res[i] = - lhs[i] * rhs[i] + rhs[i];
            fnms_res[i] = - lhs[i] * rhs[i] - rhs[i];
            hadd_res += lhs[i];
            sl_res[i] = lhs[i] << sh_nb;
            sr_res[i] = lhs[i] >> sh_nb;
        }
    }

    /***************
     * basic tests *
     ***************/

    template <class T>
    bool test_simd_basic(std::ostream& out, T& tester)
    {
        using tester_type = T;
        using vector_type = typename tester_type::vector_type;
        using value_type = typename tester_type::value_type;
        using res_type = typename tester_type::res_type;

        vector_type lhs;
        vector_type rhs;
        vector_type vres;
        res_type res(tester_type::size);
        value_type s = tester.s;
        bool success = true;
        bool tmp_success = true;

        std::string val_type = value_type_name<vector_type>();
        std::string shift = std::string(val_type.size(), '-');
        std::string name = tester.name;
        std::string name_shift = std::string(name.size(), '-');
        std::string dash(8, '-');
        std::string space(8, ' ');

        out << dash << name_shift << '-' << shift << dash << std::endl;
        out << space << name << " " << val_type << std::endl;
        out << dash << name_shift << '-' << shift << dash << std::endl << std::endl;

        out << "operator[]               : ";
        detail::load_vec(lhs, tester.lhs);
        value_type es = lhs[1];
        tmp_success = check_almost_equal(es, tester.extract_res, out);
        success = success && tmp_success;

        out << "load/store aligned       : ";
        detail::load_vec(lhs, tester.lhs);
        detail::store_vec(lhs, res);
        tmp_success = check_almost_equal(res, tester.lhs, out);
        success = success && tmp_success;
        
        out << "load/store unaligned     : ";
        lhs.load_unaligned(&tester.lhs[0]);
        lhs.store_unaligned(&res[0]);
        tmp_success = check_almost_equal(res, tester.lhs, out);
        success = success && tmp_success;

        detail::load_vec(lhs, tester.lhs);
        detail::load_vec(rhs, tester.rhs);

        out << "unary operator-          : ";
        vres = -lhs;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.minus_res, out);
        success = success && tmp_success;

        out << "operator+=(simd, simd)   : ";
        vres = lhs;
        vres += rhs;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.add_vv_res, out);
        success = success && tmp_success;

        out << "operator+=(simd, scalar) : ";
        vres = lhs;
        vres += s;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.add_vs_res, out);
        success = success && tmp_success;

        out << "operator-=(simd, simd)   : ";
        vres = lhs;
        vres -= rhs;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.sub_vv_res, out);
        success = success && tmp_success;

        out << "operator-=(simd, scalar) : ";
        vres = lhs;
        vres -= s;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.sub_vs_res, out);
        success = success && tmp_success;

        out << "operator*=(simd, simd)   : ";
        vres = lhs;
        vres *= rhs;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.mul_vv_res, out);
        success = success && tmp_success;

        out << "operator*=(simd, scalar) : ";
        vres = lhs;
        vres *= s;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.mul_vs_res, out);
        success = success && tmp_success;

        out << "operator/=(simd, simd)   : ";
        vres = lhs;
        vres /= rhs;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.div_vv_res, out);
        success = success && tmp_success;

        out << "operator/=(simd, scalar) : ";
        vres = lhs;
        vres /= s;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.div_vs_res, out);
        success = success && tmp_success;

        out << "operator+(simd, simd)    : ";
        vres = lhs + rhs;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.add_vv_res, out);
        success = success && tmp_success;

        out << "operator+(simd, scalar)  : ";
        vres = lhs + s;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.add_vs_res, out);
        success = success && tmp_success;

        out << "operator+(scalar, simd)  : ";
        vres = s + rhs;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.add_sv_res, out);
        success = success && tmp_success;
        
        out << "operator-(simd, simd)    : ";
        vres = lhs - rhs;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.sub_vv_res, out);
        success = success && tmp_success;

        out << "operator-(simd, scalar)  : ";
        vres = lhs - s;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.sub_vs_res, out);
        success = success && tmp_success;

        out << "operator-(scalar, simd)  : ";
        vres = s - rhs;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.sub_sv_res, out);
        success = success && tmp_success;

        out << "operator*(simd, simd)    : ";
        vres = lhs * rhs;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.mul_vv_res, out);
        success = success && tmp_success;

        out << "operator*(simd, scalar)  : ";
        vres = lhs * s;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.mul_vs_res, out);
        success = success && tmp_success;

        out << "operator*(scalar, simd)  : ";
        vres = s * rhs;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.mul_sv_res, out);
        success = success && tmp_success;

        out << "operator/(simd, simd)    : ";
        vres = lhs / rhs;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.div_vv_res, out);
        success = success && tmp_success;

        out << "operator/(simd, scalar)  : ";
        vres = lhs / s;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.div_vs_res, out);
        success = success && tmp_success;

        out << "operator/(scalar, simd)  : ";
        vres = s / rhs;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.div_sv_res, out);
        success = success && tmp_success;

        out << "min(simd, simd)          : ";
        vres = min(lhs, rhs);
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.min_res, out);
        success = success && tmp_success;

        out << "max(simd, simd)          : ";
        vres = max(lhs, rhs);
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.max_res, out);
        success = success && tmp_success;

        out << "fmin(simd, simd)         : ";
        vres = fmin(lhs, rhs);
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.min_res, out);
        success = success && tmp_success;

        out << "fmax(simd, simd)         : ";
        vres = fmax(lhs, rhs);
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.max_res, out);
        success = success && tmp_success;

        out << "abs(simd)                : ";
        vres = abs(lhs);
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.abs_res, out);
        success = success && tmp_success;

        out << "sqrt(simd)               : ";
        vres = sqrt(lhs);
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.sqrt_res, out);
        success = success && tmp_success;

        out << "fma(simd, simd, simd)    : ";
        vres = fma(lhs, rhs, rhs);
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.fma_res, out);
        success = success && tmp_success;

        out << "fms(simd, simd, simd)    : ";
        vres = fms(lhs, rhs, rhs);
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.fms_res, out);
        success = success && tmp_success;

        out << "fnma(simd, simd, simd)   : ";
        vres = fnma(lhs, rhs, rhs);
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.fnma_res, out);
        success = success && tmp_success;

        out << "fnms(simd, simd, simd)   : ";
        vres = fnms(lhs, rhs, rhs);
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.fnms_res, out);
        success = success && tmp_success;

        out << "hadd(simd)               : ";
        value_type sres = hadd(lhs);
        tmp_success = check_almost_equal(sres, tester.hadd_res, out);
        success = success && tmp_success;

        return success;
    }

    template <class T>
    bool test_simd_int_basic(std::ostream& out, T& tester)
    {
        using tester_type = T;
        using vector_type = typename tester_type::vector_type;
        using value_type = typename tester_type::value_type;
        using res_type = typename tester_type::res_type;

        vector_type lhs;
        vector_type rhs;
        vector_type vres;
        res_type res(tester_type::size);
        value_type s = tester.s;
        bool success = true;
        bool tmp_success = true;

        std::string val_type = value_type_name<vector_type>();
        std::string shift = std::string(val_type.size(), '-');
        std::string name = tester.name;
        std::string name_shift = std::string(name.size(), '-');
        std::string dash(8, '-');
        std::string space(8, ' ');

        out << dash << name_shift << '-' << shift << dash << std::endl;
        out << space << name << " " << val_type << std::endl;
        out << dash << name_shift << '-' << shift << dash << std::endl << std::endl;

        out << "operator[]               : ";
        detail::load_vec(lhs, tester.lhs);
        value_type es = lhs[1];
        tmp_success = check_almost_equal(es, tester.extract_res, out);
        success = success && tmp_success;

        out << "load/store aligned       : ";
        detail::load_vec(lhs, tester.lhs);
        detail::store_vec(lhs, res);
        tmp_success = check_almost_equal(res, tester.lhs, out);
        success = success && tmp_success;

        out << "load/store unaligned     : ";
        lhs.load_unaligned(&tester.lhs[0]);
        lhs.store_unaligned(&res[0]);
        tmp_success = check_almost_equal(res, tester.lhs, out);
        success = success && tmp_success;

        detail::load_vec(lhs, tester.lhs);
        detail::load_vec(rhs, tester.rhs);

        out << "unary operator-          : ";
        vres = -lhs;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.minus_res, out);
        success = success && tmp_success;

        out << "operator+=(simd, simd)   : ";
        vres = lhs;
        vres += rhs;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.add_vv_res, out);
        success = success && tmp_success;

        out << "operator+=(simd, scalar) : ";
        vres = lhs;
        vres += s;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.add_vs_res, out);
        success = success && tmp_success;

        out << "operator-=(simd, simd)   : ";
        vres = lhs;
        vres -= rhs;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.sub_vv_res, out);
        success = success && tmp_success;

        out << "operator-=(simd, scalar) : ";
        vres = lhs;
        vres -= s;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.sub_vs_res, out);
        success = success && tmp_success;

        out << "operator*=(simd, simd)   : ";
        vres = lhs;
        vres *= rhs;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.mul_vv_res, out);
        success = success && tmp_success;

        out << "operator*=(simd, scalar) : ";
        vres = lhs;
        vres *= s;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.mul_vs_res, out);
        success = success && tmp_success;

        out << "operator+(simd, simd)    : ";
        vres = lhs + rhs;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.add_vv_res, out);
        success = success && tmp_success;

        out << "operator+(simd, scalar)  : ";
        vres = lhs + s;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.add_vs_res, out);
        success = success && tmp_success;

        out << "operator+(scalar, simd)  : ";
        vres = s + rhs;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.add_sv_res, out);
        success = success && tmp_success;

        out << "operator-(simd, simd)    : ";
        vres = lhs - rhs;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.sub_vv_res, out);
        success = success && tmp_success;

        out << "operator-(simd, scalar)  : ";
        vres = lhs - s;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.sub_vs_res, out);
        success = success && tmp_success;

        out << "operator-(scalar, simd)  : ";
        vres = s - rhs;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.sub_sv_res, out);
        success = success && tmp_success;

        out << "operator*(simd, simd)    : ";
        vres = lhs * rhs;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.mul_vv_res, out);
        success = success && tmp_success;

        out << "operator*(simd, scalar)  : ";
        vres = lhs * s;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.mul_vs_res, out);
        success = success && tmp_success;

        out << "operator*(scalar, simd)  : ";
        vres = s * rhs;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.mul_sv_res, out);
        success = success && tmp_success;

        out << "min(simd, simd)          : ";
        vres = min(lhs, rhs);
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.min_res, out);
        success = success && tmp_success;

        out << "max(simd, simd)          : ";
        vres = max(lhs, rhs);
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.max_res, out);
        success = success && tmp_success;

        out << "abs(simd)                : ";
        vres = abs(lhs);
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.abs_res, out);
        success = success && tmp_success;

        out << "hadd(simd)               : ";
        value_type sres = hadd(lhs);
        tmp_success = check_almost_equal(sres, tester.hadd_res, out);
        success = success && tmp_success;

        out << "fma(simd, simd, simd)    : ";
        vres = fma(lhs, rhs, rhs);
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.fma_res, out);
        success = success && tmp_success;

        out << "fms(simd, simd, simd)    : ";
        vres = fms(lhs, rhs, rhs);
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.fms_res, out);
        success = success && tmp_success;

        out << "fnma(simd, simd, simd)   : ";
        vres = fnma(lhs, rhs, rhs);
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.fnma_res, out);
        success = success && tmp_success;

        out << "fnms(simd, simd, simd)   : ";
        vres = fnms(lhs, rhs, rhs);
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.fnms_res, out);
        success = success && tmp_success;

        out << "shift left(simd, int)    : ";
        vres = lhs << tester.sh_nb;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.sl_res, out);
        success = success && tmp_success;

        out << "shift right(simd, int)   : ";
        vres = lhs >> tester.sh_nb;
        detail::store_vec(vres, res);
        tmp_success = check_almost_equal(res, tester.sr_res, out);
        success = success && tmp_success;

        return success;
    }

    /*********************
     * conversion tester *
     *********************/

    template <std::size_t N, std::size_t A>
    struct simd_convert_tester
    {
        using int32_batch = batch<int32_t, N*2>;
        using int64_batch = batch<int64_t, N>;
        using float_batch = batch<float, N*2>;
        using double_batch = batch<double, N>;

        using int32_vector = std::vector<int32_t, aligned_allocator<int32_t, A>>;
        using int64_vector = std::vector<int64_t, aligned_allocator<int64_t, A>>;
        using float_vector = std::vector<float, aligned_allocator<float, A>>;
        using double_vector = std::vector<double, aligned_allocator<double, A>>;

        int32_batch i32pos;
        int32_batch i32neg;
        int64_batch i64pos;
        int64_batch i64neg;
        float_batch fpos;
        float_batch fneg;
        double_batch dpos;
        double_batch dneg;

        int32_vector fposres;
        int32_vector fnegres;
        int64_vector dposres;
        int64_vector dnegres;
        float_vector i32posres;
        float_vector i32negres;
        double_vector i64posres;
        double_vector i64negres;

        std::string name;

        simd_convert_tester(const std::string& name);
    };

    template <std::size_t N, std::size_t A>
    inline simd_convert_tester<N, A>::simd_convert_tester(const std::string& n)
        : name(n), i32pos(2), i32neg(-3), i64pos(2), i64neg(-3),
          fpos(float(7.4)), fneg(float(-6.2)), dpos(double(5.4)), dneg(double(-1.2)),
          fposres(2*N, 7), fnegres(2*N, -6), dposres(N, 5), dnegres(N, -1),
          i32posres(2*N, float(2)), i32negres(2*N, float(-3)),
          i64posres(N, double(2)), i64negres(N, double(-3))
    {
    }

    /*******************
     * conversion test *
     *******************/

    template <class T>
    inline bool test_simd_conversion(std::ostream& out, T& tester)
    {
        using int32_batch = typename T::int32_batch;
        using int64_batch = typename T::int64_batch;
        using float_batch = typename T::float_batch;
        using double_batch = typename T::double_batch;
        using int32_vector = typename T::int32_vector;
        using int64_vector = typename T::int64_vector;
        using float_vector = typename T::float_vector;
        using double_vector = typename T::double_vector;

        int32_batch fbres;
        int64_batch dbres;
        float_batch i32bres;
        double_batch i64bres;
        int32_vector fvres(int32_batch::size);
        int64_vector dvres(int64_batch::size);
        float_vector i32vres(float_batch::size);
        double_vector i64vres(double_batch::size);

        bool success = true;
        bool tmp_success = true;

        std::string name = tester.name;
        std::string name_shift = std::string(name.size(), '-');
        std::string dash(8, '-');
        std::string space(8, ' ');

        out << dash << name_shift << dash << std::endl;
        out << space << name << space << std::endl;
        out << dash << name_shift << dash << std::endl << std::endl;

        out << "positive float  -> int32  : ";
        fbres = to_int(tester.fpos);
        detail::store_vec(fbres, fvres);
        tmp_success = check_almost_equal(fvres, tester.fposres, out);
        success = success && tmp_success;

        out << "negative float  -> int32  : ";
        fbres = to_int(tester.fneg);
        detail::store_vec(fbres, fvres);
        tmp_success = check_almost_equal(fvres, tester.fnegres, out);
        success = success && tmp_success;

        out << "positive double -> int64  : ";
        dbres = to_int(tester.dpos);
        detail::store_vec(dbres, dvres);
        tmp_success = check_almost_equal(dvres, tester.dposres, out);
        success = success && tmp_success;

        out << "negative double -> int64  : ";
        dbres = to_int(tester.dneg);
        detail::store_vec(dbres, dvres);
        tmp_success = check_almost_equal(dvres, tester.dnegres, out);
        success = success && tmp_success;

        out << "positive int32  -> float  : ";
        i32bres = to_float(tester.i32pos);
        detail::store_vec(i32bres, i32vres);
        tmp_success = check_almost_equal(i32vres, tester.i32posres, out);
        success = success && tmp_success;

        out << "negative int32  -> float  : ";
        i32bres = to_float(tester.i32neg);
        detail::store_vec(i32bres, i32vres);
        tmp_success = check_almost_equal(i32vres, tester.i32negres, out);
        success = success && tmp_success;

        out << "positive int64  -> double : ";
        i64bres = to_float(tester.i64pos);
        detail::store_vec(i64bres, i64vres);
        tmp_success = check_almost_equal(i64vres, tester.i64posres, out);
        success = success && tmp_success;

        out << "negative int64  -> double : ";
        i64bres = to_float(tester.i64neg);
        detail::store_vec(i64bres, i64vres);
        tmp_success = check_almost_equal(i64vres, tester.i64negres, out);
        success = success && tmp_success;

        return success;
    }

    /***************
     * cast tester *
     ***************/

    template <std::size_t N, std::size_t A>
    struct simd_cast_tester
    {
        using int32_batch = batch<int32_t, N * 2>;
        using int64_batch = batch<int64_t, N>;
        using float_batch = batch<float, N * 2>;
        using double_batch = batch<double, N>;

        using int32_vector = std::vector<int32_t, aligned_allocator<int32_t, A>>;
        using int64_vector = std::vector<int64_t, aligned_allocator<int64_t, A>>;
        using float_vector = std::vector<float, aligned_allocator<float, A>>;
        using double_vector = std::vector<double, aligned_allocator<double, A>>;

        int32_batch i32_input;
        int64_batch i64_input;
        float_batch f_input;
        double_batch d_input;

        int32_vector ftoi32_res;
        int32_vector dtoi32_res;
        int64_vector ftoi64_res;
        int64_vector dtoi64_res;
        float_vector i32tof_res;
        float_vector i64tof_res;
        float_vector dtof_res;
        double_vector i32tod_res;
        double_vector i64tod_res;
        double_vector ftod_res;

        std::string name;

        simd_cast_tester(const std::string& n);
    };

    namespace detail
    {
        union bitcast
        {
            float   f[2];
            int32_t i32[2];
            int64_t i64;
            double  d;
        };
    }

    template <std::size_t N, std::size_t A>
    inline simd_cast_tester<N, A>::simd_cast_tester(const std::string& n)
        : name(n), i32_input(2), i64_input(2), f_input(3.), d_input(2.5e17),
          ftoi32_res(2 * N), dtoi32_res(2 * N), ftoi64_res(N), dtoi64_res(N),
          i32tof_res(2 * N), i64tof_res(2 * N), dtof_res(2 * N),
          i32tod_res(N), i64tod_res(N), ftod_res(N)
    {
        detail::bitcast b1;
        b1.i32[0] = i32_input[0];
        b1.i32[1] = i32_input[1];
        std::fill(i32tof_res.begin(), i32tof_res.end(), b1.f[0]);
        std::fill(i32tod_res.begin(), i32tod_res.end(), b1.d);

        detail::bitcast b2;
        b2.i64 = i64_input[0];
        std::fill(i64tod_res.begin(), i64tod_res.end(), b1.d);
        for (size_t i = 0; i < N; ++i)
        {
            i64tof_res[2 * i] = b2.f[0];
            i64tof_res[2 * i + 1] = b2.f[1];
        }

        detail::bitcast b3;
        b3.f[0] = f_input[0];
        b3.f[1] = f_input[1];
        std::fill(ftoi32_res.begin(), ftoi32_res.end(), b3.i32[0]);
        std::fill(ftoi64_res.begin(), ftoi64_res.end(), b3.i64);
        std::fill(ftod_res.begin(), ftod_res.end(), b3.d);

        detail::bitcast b4;
        b4.d = d_input[0];
        std::fill(dtoi32_res.begin(), dtoi32_res.end(), b4.i32[0]);
        std::fill(dtoi64_res.begin(), dtoi64_res.end(), b4.i64);
        for (size_t i = 0; i < N; ++i)
        {
            dtof_res[2 * i] = b4.f[0];
            dtof_res[2 * i + 1] = b4.f[1];
        }
    }

    /*************
     * cast test *
     *************/

    template <class T>
    inline bool test_simd_cast(std::ostream& out, T& tester)
    {
        using int32_batch = typename T::int32_batch;
        using int64_batch = typename T::int64_batch;
        using float_batch = typename T::float_batch;
        using double_batch = typename T::double_batch;
        using int32_vector = typename T::int32_vector;
        using int64_vector = typename T::int64_vector;
        using float_vector = typename T::float_vector;
        using double_vector = typename T::double_vector;

        int32_batch i32bres;
        int64_batch i64bres;
        float_batch fbres;
        double_batch dbres;
        int32_vector i32vres(int32_batch::size);
        int64_vector i64vres(int64_batch::size);
        float_vector fvres(float_batch::size);
        double_vector dvres(double_batch::size);

        bool success = true;
        bool tmp_success = true;

        std::string name = tester.name;
        std::string name_shift = std::string(name.size(), '-');
        std::string dash(8, '-');
        std::string space(8, ' ');

        out << dash << name_shift << dash << std::endl;
        out << space << name << space << std::endl;
        out << dash << name_shift << dash << std::endl << std::endl;

        out << "cast int32  -> float  : ";
        fbres = bitwise_cast<float_batch>(tester.i32_input);
        detail::store_vec(fbres, fvres);
        tmp_success = check_almost_equal(fvres, tester.i32tof_res, out);
        success = success && tmp_success;

        out << "cast int32  -> double : ";
        dbres = bitwise_cast<double_batch>(tester.i32_input);
        detail::store_vec(dbres, dvres);
        tmp_success = check_almost_equal(dvres, tester.i32tod_res, out);
        success = success && tmp_success;

        out << "cast int64  -> float  : ";
        fbres = bitwise_cast<float_batch>(tester.i64_input);
        detail::store_vec(fbres, fvres);
        tmp_success = check_almost_equal(fvres, tester.i64tof_res, out);
        success = success && tmp_success;

        out << "cast int64  -> double : ";
        dbres = bitwise_cast<double_batch>(tester.i64_input);
        detail::store_vec(dbres, dvres);
        tmp_success = check_almost_equal(dvres, tester.i64tod_res, out);
        success = success && tmp_success;

        out << "cast float  -> int32  : ";
        i32bres = bitwise_cast<int32_batch>(tester.f_input);
        detail::store_vec(i32bres, i32vres);
        tmp_success = check_almost_equal(i32vres, tester.ftoi32_res, out);
        success = success && tmp_success;

        out << "cast float  -> int64  : ";
        i64bres = bitwise_cast<int64_batch>(tester.f_input);
        detail::store_vec(i64bres, i64vres);
        tmp_success = check_almost_equal(i64vres, tester.ftoi64_res, out);
        success = success && tmp_success;

        out << "cast float  -> double : ";
        dbres = bitwise_cast<double_batch>(tester.f_input);
        detail::store_vec(dbres, dvres);
        tmp_success = check_almost_equal(dvres, tester.ftod_res, out);
        success = success && tmp_success;

        out << "cast double -> int32  : ";
        i32bres = bitwise_cast<int32_batch>(tester.d_input);
        detail::store_vec(i32bres, i32vres);
        tmp_success = check_almost_equal(i32vres, tester.dtoi32_res, out);
        success = success && tmp_success;
        
        out << "cast double -> int64  : ";
        i64bres = bitwise_cast<int64_batch>(tester.d_input);
        detail::store_vec(i64bres, i64vres);
        tmp_success = check_almost_equal(i64vres, tester.dtoi64_res, out);
        success = success && tmp_success;

        out << "cast double -> float  : ";
        fbres = bitwise_cast<float_batch>(tester.d_input);
        detail::store_vec(fbres, fvres);
        tmp_success = check_almost_equal(fvres, tester.dtof_res, out);
        success = success && tmp_success;

        return success;
    }

}

#endif

