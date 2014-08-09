#pragma once
#ifndef SFZ_MATH_RECTANGLE_HPP
#define SFZ_MATH_RECTANGLE_HPP

#include <stdexcept>
#include "sfz/math/Vector.hpp"
#include "sfz/math/Alignment.hpp"

// Forward declares Circle, is included after complete declaration of Rectangle.
namespace sfz {
	template<typename T>
	class Circle;
}

namespace sfz {

	/**
	 * @brief A class representing a Rectangle.
	 *
	 * The two alignment variables decide how the Rectangle is anchored to the position.
	 *
	 * Beware if using integral types, some things like changing alignment and overlap checks might mess up due to
	 * truncation.
	 *
	 * @param T the element type
	 *
	 * @author Peter Hillerström <peter@hstroem.se>
	 * @date 2014-08-08
	 */
	template<typename T>
	class Rectangle final {
	public:
		// Static constants
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		/**
		 * @brief The default HorizontalAlign.
		 */
		static const HorizontalAlign DEFAULT_HORIZONTAL_ALIGN;

		/**
		 * @brief The default VerticalAlign.
		 */
		static const VerticalAlign DEFAULT_VERTICAL_ALIGN;

		// Constructors and destructors
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		Rectangle() = delete;

		/**
		 * @brief Basic copy-constructor.
		 * @param rect the Rectangle to copy
		 */
		Rectangle(const Rectangle<T>& rect);

		/**
		 * @brief Rectangle constructor.
		 * If you don't specify the alignment variables they will be set to the default values.
		 * @throw std::invalid_argument if width or height < 0
		 * @param position the position
		 * @param dimensions the dimensions
		 * @param horizontalAlign the HorizontalAlign
		 * @param verticalAlign the VerticalAlign
		 */
		Rectangle(const vec2<T>& position, const vec2<T>& dimensions, 
		          HorizontalAlign horizontalAlign = DEFAULT_HORIZONTAL_ALIGN, 
		          VerticalAlign verticalAlign = DEFAULT_VERTICAL_ALIGN);

		/**
		 * @brief Rectangle constructor.
		 * If you don't specify the alignment variables they will be set to the default values.
		 * @throw std::invalid_argument if width or height < 0
		 * @param position the position
		 * @param width the width
		 * @param height the height
		 * @param horizontalAlign the HorizontalAlign
		 * @param verticalAlign the VerticalAlign
		 */
		Rectangle(const vec2<T>& position, T width, T height, 
		          HorizontalAlign horizontalAlign = DEFAULT_HORIZONTAL_ALIGN, 
		          VerticalAlign verticalAlign = DEFAULT_VERTICAL_ALIGN);

		/**
		 * @brief Rectangle constructor.
		 * If you don't specify the alignment variables they will be set to the default values.
		 * @throw std::invalid_argument if width or height < 0
		 * @param x the x-position
		 * @param y the y-position
		 * @param width the width
		 * @param height the height
		 * @param horizontalAlign the HorizontalAlign
		 * @param verticalAlign the VerticalAlign
		 */
		Rectangle(T x, T y, T width, T height, 
		          HorizontalAlign horizontalAlign = DEFAULT_HORIZONTAL_ALIGN, 
		          VerticalAlign verticalAlign = DEFAULT_VERTICAL_ALIGN);

		~Rectangle() = default;

		// Public member functions
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		/**
		 * @brief Returns whether the specified vector is inside this Rectangle or not.
		 * It's worth noting that this function uses 
		 * @param point the specified vector
		 * @return whether the specified vector is inside this Rectangle or not
		 */
		bool overlap(const vec2<T>& point) const;

		/**
		 * @brief Returns whether the specified Rectangle overlaps with this Rectangle or not.
		 * @param rectangle the specified rectangle
		 * @return whether the specified Rectangle overlaps with this Rectangle or not
		 */
		bool overlap(const Rectangle<T>& rect) const;

		/**
		 * @brief Returns whether the specified Circle overlaps with this Rectangle or not.
		 * @param circle the specified circle
		 * @return whether the specified Circle overlaps with this Rectangle or not
		 */
		bool overlap(const Circle<T>& circle) const;

		// Getters
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		/**
		 * @brief Returns the position of this Rectangle.
		 * @return position of this Rectangle
		 */
		vec2<T> getPosition() const;

		/**
		 * @brief Returns the x-position of this Rectangle.
		 * @return x-position of this Rectangle
		 */
		T getX() const;

		/**
		 * @brief Returns the y-position of this Rectangle.
		 * @return y-position of this Rectangle
		 */
		T getY() const;

		/**
		 * @brief Returns the dimensions of this Rectangle.
		 * @return dimensions of this rectangle
		 */
		vec2<T> getDimensions() const;

		/**
		 * @brief Returns the width of this Rectangle.
		 * @return width of this Rectangle
		 */
		T getWidth() const;

		/**
		 * @brief Returns the height of this Rectangle.
		 * @return height of this Rectangle
		 */
		T getHeight() const;

		/**
		 * @brief Returns the HorizontalAlign of this Rectangle.
		 * @return HorizontalAlign of this Rectangle
		 */
		HorizontalAlign getHorizontalAlign() const;

		/**
		 * @brief Returns the VerticalAlign of this Rectangle.
		 * @return VerticalAlign of this Rectangle
		 */
		VerticalAlign getVerticalAlign() const;

		// Setters
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		/**
		 * @brief Sets the position.
		 * @param position the position to set
		 */
		void setPosition(const vec2<T>& position);

		/**
		 * @brief Sets the position.
		 * @param x the x-position to set
		 * @param y the y-position to set
		 */
		void setPosition(T x, T y);

		/**
		 * @brief Sets the x-position.
		 * @param x the x-position to set
		 */
		void setX(T x);
		
		/**
		 * @brief Sets the y-position.
		 * @param y the y-position to set
		 */
		void setY(T y);

		/**
		 * @brief Sets the dimensions.
		 * @throw std::invalid_argument if width or height < 0
		 * @param dimensions the dimensions to set
		 */
		void setDimensions(const vec2<T>& dimensions);

		/**
		 * @brief Sets the dimensions.
		 * @throw std::invalid_argument if width or height < 0
		 * @param width the width to set
		 * @param height the height to set
		 */
		void setDimensions(T width, T height);

		/**
		 * @brief Sets the width.
		 * @throw std::invalid_argument if width < 0
		 * @param width the width to set
		 */
		void setWidth(T width);

		/**
		 * @brief Sets the height.
		 * @throw std::invalid_argument if height < 0
		 * @param height the height to set
		 */
		void setHeight(T height);

		/**
		 * @brief Simply sets the HorizontalAlign wihout doing anything else.
		 * Doesn't update the position, so the Rectangle is actually shifted slightly by this function. If this is
		 * unintended you should call changeHorizontalAlign() instead which also updates the position.
		 * @see changeHorizontalAlign()
		 * @param horizontalAlign the HorizontalAlign to set
		 */
		void setHorizontalAlign(HorizontalAlign horizontalAlign);

		/**
		 * @brief Simply sets the VerticalAlign wihout doing anything else.
		 * Doesn't update the position, so the Rectangle is actually shifted slightly by this function. If this is
		 * unintended you should call changeVerticalAlign() instead which also updates the position.
		 * @see changeVerticalAlign()
		 * @param verticalAlign the VerticalAlign to set
		 */
		void setVerticalAlign(VerticalAlign verticalAlign);

		/**
		 * @brief Changes the HorizontalAlign of this Rectangle and updates the internal position reflecting this.
		 * The position is updated so the Rectangle's actual position is the same afterwards, i.e. not shifted. If 
		 * this is not wanted setHorizontalAlign() should be used.
		 * @see setHorizontalAlign()
		 * @param horizontalAlign the HorizontalAlign to set
		 */
		void changeHorizontalAlign(HorizontalAlign horizontalAlign);

		/**
		 * @brief Changes the VerticalAlign of this Rectangle and updates the internal position reflecting this.
		 * The position is updated so the Rectangle's actual position is the same afterwards, i.e. not shifted. If
		 * this is not wanted setVerticalAlign() should be used.
		 * @see setVerticalAlign()
		 * @param verticalAlign the VerticalAlign to set
		 */
		void changeVerticalAlign(VerticalAlign verticalAlign);

	private:

		// Members
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		vec2<T> position;
		vec2<T> dimensions;
		HorizontalAlign horizontalAlign;
		VerticalAlign verticalAlign;

		// Private helper functions
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		T requireNonNegative(T value) const;
	};
}
#include "sfz/math/Circle.hpp"
#include "Rectangle.inl"
#endif