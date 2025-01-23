# Validates hardware capabilities
class CapabilityValidator
  def self.validate_group(group)
    return true unless %w[raspberry].include?(group)

    unless raspberry_pi?
      puts "\nSkipping 'raspberry' - Raspberry Pi capability not detected"
      return false
    end
    true
  end

  def self.raspberry_pi?
    # Method 1: Check for Raspberry Pi specific file
    if File.exist?('/proc/device-tree/model')
      device_model = File.read('/proc/device-tree/model')
      return true if device_model.include?('Raspberry Pi')
    end
    # Method 2: Check for ARM architecture and Broadcom chip
    if %w[arm aarch64].include?(RbConfig::CONFIG['target_cpu']) && 
       File.exist?('/proc/cpuinfo') && File.read('/proc/cpuinfo') =~ /BCM\d+/
      return true
    end

    false
  end
end
