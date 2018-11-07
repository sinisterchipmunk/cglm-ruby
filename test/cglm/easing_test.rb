require "test_helper"

class CglmCamTest < Minitest::Test
  include CGLM::Easing

  def test_linear
    assert_kind_of Numeric, linear(0.5)
  end


  def test_sine_in
    assert_kind_of Numeric, sine_in(0.5)
  end


  def test_sine_out
    assert_kind_of Numeric, sine_out(0.5)
  end


  def test_sine_inout
    assert_kind_of Numeric, sine_inout(0.5)
  end


  def test_quad_in
    assert_kind_of Numeric, quad_in(0.5)
  end


  def test_quad_out
    assert_kind_of Numeric, quad_out(0.5)
  end


  def test_quad_inout
    assert_kind_of Numeric, quad_inout(0.5)
  end


  def test_cubic_in
    assert_kind_of Numeric, cubic_in(0.5)
  end


  def test_cubic_out
    assert_kind_of Numeric, cubic_out(0.5)
  end


  def test_cubic_inout
    assert_kind_of Numeric, cubic_inout(0.5)
  end


  def test_quart_in
    assert_kind_of Numeric, quart_in(0.5)
  end


  def test_quart_out
    assert_kind_of Numeric, quart_out(0.5)
  end


  def test_quart_inout
    assert_kind_of Numeric, quart_inout(0.5)
  end


  def test_quint_in
    assert_kind_of Numeric, quint_in(0.5)
  end


  def test_quint_out
    assert_kind_of Numeric, quint_out(0.5)
  end


  def test_quint_inout
    assert_kind_of Numeric, quint_inout(0.5)
  end


  def test_exp_in
    assert_kind_of Numeric, exp_in(0.5)
  end


  def test_exp_out
    assert_kind_of Numeric, exp_out(0.5)
  end


  def test_exp_inout
    assert_kind_of Numeric, exp_inout(0.5)
  end


  def test_circ_in
    assert_kind_of Numeric, circ_in(0.5)
  end


  def test_circ_out
    assert_kind_of Numeric, circ_out(0.5)
  end


  def test_circ_inout
    assert_kind_of Numeric, circ_inout(0.5)
  end


  def test_back_in
    assert_kind_of Numeric, back_in(0.5)
  end


  def test_back_out
    assert_kind_of Numeric, back_out(0.5)
  end


  def test_back_inout
    assert_kind_of Numeric, back_inout(0.5)
  end


  def test_elast_in
    assert_kind_of Numeric, elast_in(0.5)
  end


  def test_elast_out
    assert_kind_of Numeric, elast_out(0.5)
  end


  def test_elast_inout
    assert_kind_of Numeric, elast_inout(0.5)
  end


  def test_bounce_out
    assert_kind_of Numeric, bounce_out(0.5)
  end


  def test_bounce_in
    assert_kind_of Numeric, bounce_in(0.5)
  end


  def test_bounce_inout
    assert_kind_of Numeric, bounce_inout(0.5)
  end
end
